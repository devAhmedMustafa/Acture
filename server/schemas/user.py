from pydantic import BaseModel

class TokenData(BaseModel):
    token: str

class UserResponse(BaseModel):
    email: str
    token: str