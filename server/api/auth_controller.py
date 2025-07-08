from fastapi import APIRouter, Depends, HTTPException
from schemas.user import TokenData, UserResponse
from services.user_service import UserService, get_user_service

router = APIRouter(prefix="/auth", tags=["auth"])


@router.post("/google-login", response_model=UserResponse)
async def google_login(google_token: TokenData, user_service: UserService = Depends(get_user_service)):
    try:
        user, jwt_token = user_service.google_authenticate(google_token.token)
        return UserResponse(email=user.email, token=jwt_token)
    except ValueError as e:
        print(f"Authentication error: {e}")
        raise HTTPException(status_code=400, detail=str(e))
    