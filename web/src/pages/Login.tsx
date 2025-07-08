import GoogleLoginButton from "../components/GoogleLoginButton";

export default function LoginPage() {

    return (
        <div className="flex items-center justify-center min-h-screen bg-gray-100">
            <div className="bg-white p-8 rounded shadow-md w-full max-w-sm">
                <h2 className="text-2xl font-bold mb-6 text-center">Login</h2>
                <GoogleLoginButton />
            </div>
        </div>
    );
}