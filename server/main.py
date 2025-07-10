from fastapi import FastAPI
from fastapi.middleware.cors import CORSMiddleware
from api import auth_controller, rooms_controller
from repositories.session import engine
from models.base import Base

Base.metadata.create_all(bind=engine)

app = FastAPI()

origins = [
    "*",
    "http://localhost:5173",
    "http://localhost"
]

app.add_middleware(CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

app.include_router(auth_controller.router)
app.include_router(rooms_controller.router)
