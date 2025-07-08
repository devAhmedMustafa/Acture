from fastapi import Depends
import requests
from repositories.user import UserRepository, get_user_repository
from core.config import settings
from middlewares.jwt import create_jwt_token

class UserService:
    def __init__(self, repo: UserRepository):
        self.user_repo = repo

    def google_authenticate(self, google_token: str):
        google_res = requests.get(
            f"https://oauth2.googleapis.com/tokeninfo?id_token={google_token}"
        )

        if not google_res.ok:
            raise ValueError("Invalid Google token")
        
        res = google_res.json()

        if res.get("aud") != settings.CLIENT_ID:
            raise ValueError("Invalid Google token")
        
        email = res.get("email")
        if not email:
            raise ValueError("Email not found in Google token")
        
        user = self.user_repo.get_by_email(email) or self.user_repo.create(email)
        jwt_token = create_jwt_token({"email": user.email})
        return user, jwt_token
    

def get_user_service(db: UserRepository = Depends(get_user_repository)):
    return UserService(db)