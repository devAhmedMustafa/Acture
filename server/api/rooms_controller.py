from fastapi import APIRouter, HTTPException, Form, File, Depends, Request, Query
from fastapi import UploadFile, WebSocket, WebSocketDisconnect
from fastapi.responses import JSONResponse
from services.room_manager import RoomManager
from middlewares.jwt import get_current_useremail

router = APIRouter(prefix="/rooms", tags=["rooms"])

global manager
manager = RoomManager()

@router.post("/host")
async def host_room(
    request: Request,
    spi_file: UploadFile = File(...), 
):

    token = request.headers.get("Authorization")
    if not token:
        return JSONResponse(status_code=401, content={"error": "Authorization token is required."})
    
    host_email = get_current_useremail(token)

    if not spi_file.filename.endswith('.spi'):
        return JSONResponse(status_code=400, content={"error": "Invalid file type. Please upload a .spi file."})
    
    content = await spi_file.read()

    room = manager.create_room(host_email, content)

    return JSONResponse(status_code=201, content={"room_id": room.room_id, "message": "Room created successfully."})

@router.websocket("/join/{room_id}")
async def websocket_endpoint(
    websocket: WebSocket, 
    room_id: str, 
    client_id: str = Query(...)
    ):

    room = manager.get_room(room_id)
    if not room:
        await websocket.accept()
        await websocket.close(code=1003, reason="Room not found.")
        return
    
    await websocket.accept()
    
    await room.add_client(client_id, websocket)

    try:
        while True:
            data = await websocket.receive_text()
            if not data:
                await websocket.close(code=1008, reason="Empty message received.")
                continue
            
            await manager.broadcast_message(room_id, data)

    except WebSocketDisconnect:
        room.clients.pop(client_id, None)
        room.VEs.pop(client_id, None)
        await manager.broadcast_message(room_id, f"Client {client_id} has disconnected.")



@router.post("/{room_id}/traverse")
async def virtual_traverse(
    request: Request,
    room_id: str,
    thread: int = Form(...)
):
    token = request.headers.get("Authorization")
    if not token:
        return JSONResponse(status_code=401, content={"error": "Authorization token is required."})
    
    host_email = get_current_useremail(token)

    if not host_email:
        return JSONResponse(status_code=403, content={"error": "Invalid or expired token."})
    
    room = manager.get_room(room_id)
    if not room:
        return JSONResponse(status_code=404, content={"error": "Room not found."})
    
    room.VEs[host_email].travel(thread)
    return JSONResponse(status_code=200, content={"message": "Virtual traverse successful."})


@router.get("/{room_id}/move")
async def travel_in_room(
    request: Request,
    room_id: str,
):
    token = request.headers.get("Authorization")
    if not token:
        return JSONResponse(status_code=401, content={"error": "Authorization token is required."})
    
    host_email = get_current_useremail(token)
    if not host_email:
        return JSONResponse(status_code=403, content={"error": "Invalid or expired token."})
    
    room = manager.get_room(room_id)
    if not room:
        return JSONResponse(status_code=404, content={"error": "Room not found."})
    
    if host_email != room.host:
        return JSONResponse(status_code=403, content={"error": "Only the host can travel."})
    
    await manager.broadcast_media_update(room_id)
    return JSONResponse(status_code=200, content={"message": "Travel successful."})


@router.get("/{room_id}/trigger_station")
async def trigger_station(
    request: Request,
    room_id: str,
):
    token = request.headers.get("Authorization")
    if not token:
        return JSONResponse(status_code=401, content={"error": "Authorization token is required."})
    
    host_email = get_current_useremail(token)
    if not host_email:
        return JSONResponse(status_code=403, content={"error": "Invalid or expired token."})
    
    room = manager.get_room(room_id)

    if not room:
        return JSONResponse(status_code=404, content={"error": "Room not found."})
    
    if host_email != room.host:
        return JSONResponse(status_code=403, content={"error": "Only the host can trigger stations."})
    
    await manager.broadcast_station_previews(room_id)
    return JSONResponse(status_code=200, content={"message": "Station previews triggered."})
            
    