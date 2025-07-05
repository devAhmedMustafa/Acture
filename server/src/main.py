from fastapi import FastAPI, UploadFile
from fastapi.responses import JSONResponse
from middlewares.room_manager import RoomManager

app = FastAPI()

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
