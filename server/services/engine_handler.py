from lib.pystation import *
import uuid
import tempfile
import os

class EngineHandler:
    def __init__(self, spi_file_bytes: bytes):
        self.engine : Engine = Engine()
        self.spi_file = self._save_temp_file(spi_file_bytes)
        self.load_spi()

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
