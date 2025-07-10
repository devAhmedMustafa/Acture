from sqlalchemy import Column, String, UUID
from .base import Base
import uuid

class User(Base):
    __tablename__ = 'User'

    id = Column(UUID, primary_key=True, index=True, default=lambda: str(uuid.uuid4()))
    email = Column(String, unique=True, index=True)
    