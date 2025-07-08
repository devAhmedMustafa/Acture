import { GoogleLogin, GoogleOAuthProvider } from "@react-oauth/google";
import { useAuth } from "../context/AuthContext";
import api from "../utils/api";

const GOOGLE_CLIENT_ID = "441746363812-qps3ctm0hvo5m2idfrvlu6ngieud9c6i.apps.googleusercontent.com";

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

    return (
        <GoogleOAuthProvider clientId={GOOGLE_CLIENT_ID}>
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
