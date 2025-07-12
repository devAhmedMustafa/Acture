from lib.pystation import *


class EngineHandler:
    def __init__(self, spi_file_path: str):
        self.engine : Engine = Engine()
        self.spi_file_path = spi_file_path
        self.load_spi()
        self.engine.play()
    
    def load_spi(self):
        deserializer = StationNetworkSerializer(self.engine)
        deserializer.import_spi_file(self.spi_file_path)

    def get_engine(self) -> Engine:
        return self.engine
    
    def get_current_media(self) -> dict:
        return self.engine.get_media_binder().data_to_bind(0)[0].to_dict()
    
    def travel(self, thread: str) -> None:
        self.engine.travel(thread)

    def play(self) -> None:
        self.engine.play()
    
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

    def trigger_station(self) -> dict:
        self.engine.on_update(0)
        data = self.engine.receive_channel_data()
        if not data:
            print("No data received from the station.")
            raise ValueError("No data received from the station.")
            
        return data.to_dict()