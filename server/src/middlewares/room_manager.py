import uuid
from fastapi import WebSocket

class Room:
    def __init__(self, room_id: str, spi_file: bytes):
        self.room_id = room_id
        self.spi_file = spi_file
        self.clients: set[WebSocket] = set()

class RoomManager:
    def __init__(self):
        self.rooms: dict[str, Room] = {}

    def create_room(self, spi_file: bytes) -> Room:
        room_id = str(uuid.uuid4())
        
        if room_id in self.rooms:
            raise ValueError(f"Room {room_id} already exists.")
        
        self.rooms[room_id] = Room(room_id, spi_file)

    def get_room(self, room_id: str) -> Room:
        if room_id not in self.rooms:
            raise ValueError(f"Room {room_id} does not exist.")
        
        return self.rooms[room_id]
    
    def delete_room(self, room_id: str):
        if room_id not in self.rooms:
            raise ValueError(f"Room {room_id} does not exist.")
        
        del self.rooms[room_id]
        