import uuid
import os
import tempfile

def _save_temp_file(spi_file_bytes: bytes) -> str:
    temp_dir = tempfile.gettempdir()
    filename = f"{uuid.uuid4()}.spi"
    full_path = os.path.join(temp_dir, filename)
    with open(full_path, 'wb') as f:
        f.write(spi_file_bytes)
    return full_path