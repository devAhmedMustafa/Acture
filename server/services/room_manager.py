import uuid
from fastapi import WebSocket
from services.engine_handler import EngineHandler, VirtualEngine

class Room:
    def __init__(self, room_id: str, host_id: str, spi_file: bytes):
        self.room_id = room_id
        self.host = host_id
        self.spi_file = spi_file
        self.engine = EngineHandler(spi_file)
        self.clients = dict[str, WebSocket]()  # WebSocket connections for each client
        self.VEs = dict[str, VirtualEngine]()  # Virtual engines for each client

    async def add_client(self, client_id: str, websocket: WebSocket):
            
        if client_id in self.clients:
            pass
        
        self.clients[client_id] = websocket
        self.VEs[client_id] = VirtualEngine()

        temp_traverse = self.engine.get_engine().get_station_network().get_station_by_id(0)
        for _ in range(self.level()):

            self.VEs[client_id].station_stack.append(
                temp_traverse.get_id()
            )

            traverse_idx = temp_traverse.get_connected_station(0)
            temp_traverse = self.engine.get_engine().get_station_network().get_station_by_id(traverse_idx)

        payload = {}

        try:
            payload = self.engine.get_virtual_media(
                self.VEs[client_id].station_stack[-2],
                self.VEs[client_id].action_stack[-1] if self.VEs[client_id].action_stack else 0
            )
        except Exception as e:
            print(f"Error getting virtual media: {e}")


        await self.clients[client_id].send_json({
            "type": "media",
            "payload": payload
        })
    
    def virtual_traverse(self, client_id: str, thread: int):
        if client_id not in self.VEs:
            self.VEs[client_id] = VirtualEngine()

        self.VEs[client_id].action_stack.append(thread)
        prev_station = self.VEs[client_id].station_stack[-1] if self.VEs[client_id].station_stack else 0
        self.VEs[client_id].station_stack.append(self.engine.virtual_traverse(prev_station, thread))

    def level(self) -> int:
        return max(
            len(ve.station_stack) for ve in self.VEs.values()
        ) if self.VEs else 0

class RoomManager:
    def __init__(self):
        self.rooms: dict[str, Room] = {}

    def create_room(self, host_id: str, spi_file: bytes) -> Room:
        room_id = str(uuid.uuid4())
        
        if room_id in self.rooms:
            raise ValueError(f"Room {room_id} already exists.")
        
        room = Room(room_id, host_id, spi_file)
        self.rooms[room_id] = room

        room.engine.load_spi()

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
                cooresponding_media = room.engine.get_virtual_media(
                    virtual_engine.station_stack[-2],
                    virtual_engine.action_stack[-1]
                )

                await room.clients[client].send_json({"type": "media", "payload": cooresponding_media})

            except Exception as e:
                print(f"Error sending media update to client {client}: {e}")
                room.clients.pop(client, None)
        
