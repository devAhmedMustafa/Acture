import { GoogleLogin, GoogleOAuthProvider } from "@react-oauth/google";
import { useAuth } from "../contexts/AuthContext";
import api from "../utils/api";
import { useEffect } from "react";

export default function GoogleLoginButton() {

    const {login} = useAuth();

    const handleSuccess =  async (credentialResponse: any) => {
        const {credential} = credentialResponse;
        try {
            const res = await api.post('/auth/google-login', { token: credential });
            const { token, email } = res.data;

            login({
                name: email.split('@')[0],
                email: email,
            }, token);
            
        }
        catch (error) {
            console.error("Login failed:", error);
            alert("Login failed. Please try again.");
        }
    }

    useEffect(() => {
        console.log(import.meta.env.VITE_GOOGLE_CLIENT_ID);
    }, []);

    return (
        <GoogleOAuthProvider clientId={import.meta.env.VITE_GOOGLE_CLIENT_ID}>
            <GoogleLogin
                onSuccess={handleSuccess}
                onError={() => {
                    console.error("Login Failed");
                    alert("Login failed. Please try again.");
                }}
                logo_alignment="left"
            />
        </GoogleOAuthProvider> 
    )

}
