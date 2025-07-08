from fastapi import FastAPI, UploadFile, WebSocket, WebSocketDisconnect
from fastapi.responses import JSONResponse
from fastapi.middleware.cors import CORSMiddleware
from services.room_manager import RoomManager
from api import auth_controller
from repositories.session import engine
from models.base import Base

Base.metadata.create_all(bind=engine)

app = FastAPI()

origins = [
    "http://localhost:5173"
]

app.add_middleware(CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

app.include_router(auth_controller.router)

manager = RoomManager()

@app.get("/", response_class=JSONResponse)
def read_root():
    return {"message": "Welcome to the Pystation API!"}

@app.post("/host")
async def host_room(spi_file: UploadFile):

    if not spi_file.filename.endswith('.spi'):
        return JSONResponse(status_code=400, content={"error": "Invalid file type. Please upload a .spi file."})
    
    content = await spi_file.read()

    room = manager.create_room(content)

    return JSONResponse(status_code=201, content={"room_id": room.room_id, "message": "Room created successfully."})

@app.websocket("/ws/room/{room_id}")
async def websocket_endpoint(websocket: WebSocket, room_id: str):
    room = manager.get_room(room_id)
    if not room:
        await websocket.accept()
        await websocket.close(code=1003, reason="Room not found.")
        return
    
    await websocket.accept()
    room.clients.add(websocket)

    try:
        while True:
            data = await websocket.receive_text()
            if not data:
                await websocket.close(code=1008, reason="Empty message received.")
                continue
            
            await manager.broadcast_message(room_id, data)

    except WebSocketDisconnect:
        room.clients.remove(websocket)

