from jose import jwt, JWTError
from fastapi import HTTPException, Depends
from fastapi.security import OAuth2PasswordBearer
from core.config import settings
from repositories.session import SessionLocal
from repositories.user import UserRepository

oauth2_scheme = OAuth2PasswordBearer(tokenUrl="token")

def create_jwt_token(data: dict) -> str:
    return jwt.encode(data, settings.SECRET_KEY, algorithm="HS256")

def decode_jwt_token(token: str) -> dict:
    try:
        payload = jwt.decode(token.replace("Bearer ", ""), settings.SECRET_KEY, algorithms=settings.ALGORITHM)
        return payload
    except JWTError:
        raise HTTPException(
            status_code=401,
            detail="Could not validate credentials",
            headers={"WWW-Authenticate": "Bearer"},
        )
    
def get_current_useremail(token: str = Depends(oauth2_scheme)):
    payload = decode_jwt_token(token)
    email: str = payload.get("email")
    if email is None:
        raise HTTPException(
            status_code=401,
            detail="Could not validate credentials",
            headers={"WWW-Authenticate": "Bearer"},
        )
    
    return email