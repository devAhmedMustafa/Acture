import uuid
from fastapi import WebSocket
from services.engine_handler import EngineHandler
from utils.files import _save_temp_file

class Room:
    def __init__(self, room_id: str, host_id: str, spi_file: bytes):
        self.room_id = room_id
        self.host = host_id
        self.spi_file = spi_file
        self.spi_file_path = _save_temp_file(spi_file)
        self.clients = dict[str, WebSocket]()  # WebSocket connections for each client
        self.VEs = dict[str, EngineHandler]()  # Virtual engines for each client

    async def add_client(self, client_id: str, websocket: WebSocket):
            
        if client_id in self.clients:
            pass
        
        self.clients[client_id] = websocket
        self.VEs[client_id] = EngineHandler(self.spi_file_path)

        payload = {}


        try:
            payload = self.VEs[client_id].get_current_media()
        except Exception as e:
            print(f"Error getting virtual media: {e}")

        await self.clients[client_id].send_json({
            "type": "media",
            "payload": payload
        })

class RoomManager:
    def __init__(self):
        self.rooms: dict[str, Room] = {}

    def create_room(self, host_id: str, spi_file: bytes) -> Room:
        room_id = str(uuid.uuid4())
        
        if room_id in self.rooms:
            raise ValueError(f"Room {room_id} already exists.")
        
        room = Room(room_id, host_id, spi_file)
        self.rooms[room_id] = room

        return room

    def get_room(self, room_id: str) -> Room:
        if room_id not in self.rooms:
            raise ValueError(f"Room {room_id} does not exist.")
        
        return self.rooms[room_id]
    
    def delete_room(self, room_id: str):
        if room_id not in self.rooms:
            raise ValueError(f"Room {room_id} does not exist.")
        
        del self.rooms[room_id]

    async def broadcast_message(self, room_id: str, message: str):
        if room_id not in self.rooms:
            raise ValueError(f"Room {room_id} does not exist.")
        
        room = self.rooms[room_id]
        for client in room.clients.values():
            try:
                await client.send_text(message)
            except:
                room.clients.pop(client, None)
       
    async def broadcast_media_update(self, room_id: str):
        if room_id not in self.rooms:
            raise ValueError(f"Room {room_id} does not exist.")
        
        room = self.rooms[room_id]

        for client in room.clients.keys():
            try:
                virtual_engine = room.VEs[client]
                cooresponding_media = virtual_engine.get_current_media()

                await room.clients[client].send_json({"type": "media", "payload": cooresponding_media})

            except Exception as e:
                print(f"Error sending media update to client {client}: {e}")
                room.clients.pop(client, None)
        
    async def broadcast_station_previews(self, room_id: str):
        if room_id not in self.rooms:
            raise ValueError(f"Room {room_id} does not exist.")
        
        room = self.rooms[room_id]
        for client in list(room.clients.keys()):
            # if client == room.host:
            #     continue
            try:
                virtual_engine = room.VEs[client]
                station_preview = virtual_engine.trigger_station()

                await room.clients[client].send_json(
                    {"type": "interactivity", "payload": station_preview}
                    )
                
            except Exception as e:
                print(f"Error sending station preview to client {client}: {e}")
                room.clients.pop(client, None)

