from lib.pystation import *
import uuid
import tempfile
import os

class VirtualEngine:
    def __init__(self):
        self.station_stack = [0]
        self.action_stack = [0]

class EngineHandler:
    def __init__(self, spi_file_bytes: bytes):
        self.engine : Engine = Engine()
        self.spi_file = self._save_temp_file(spi_file_bytes)
        self.load_spi()
        self.engine.travel(0)

    def _save_temp_file(self, spi_file_bytes: bytes) -> str:
        temp_dir = tempfile.gettempdir()
        filename = f"{uuid.uuid4()}.spi"
        full_path = os.path.join(temp_dir, filename)
        with open(full_path, 'wb') as f:
            f.write(spi_file_bytes)
        return full_path
    
    def load_spi(self):
        deserializer = StationNetworkSerializer(self.engine)
        deserializer.import_spi_file(self.spi_file)

    def get_engine(self) -> Engine:
        return self.engine
    
    def get_current_media(self) -> dict:
        return self.engine.get_media_binder().data_to_bind(0)[0].to_dict()
    
    def virtual_traverse(self, station_id: str, thread: int) -> int:
        station = self.engine.get_station_network().get_station_by_id(station_id)
        if not station:
            raise ValueError(f"Station with ID {station_id} does not exist.")
        
        return station.get_connected_station(thread)
    
    def get_virtual_media(self, station_id: str, thread: int) -> list:

        station = self.engine.get_station_network().get_station_by_id(station_id)

        if not station:
            print(f"Station with ID {station_id} does not exist.")
            raise ValueError(f"Station with ID {station_id} does not exist.")

        verse = station.get_connected_verse(thread)

        if not verse:
            print(f"No verse connected to station {station_id} on thread {thread}.")
            raise ValueError(f"No verse connected to station {station_id} on thread {thread}.")
        
        clip = verse.tracks[0].get_clip(0)
        
        if not clip:
            print(f"No clip found in verse {verse.get_id()} on station {station_id}.")
            raise ValueError(f"No clip found in verse {verse.get_id()} on station {station_id}.")

        return clip.to_dict()
