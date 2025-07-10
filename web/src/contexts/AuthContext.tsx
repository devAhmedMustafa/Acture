import { createContext, useContext, useState } from "react";

interface AuthContextType {
    isAuthenticated: boolean;

    user: {
        name: string;
        email: string;
    } | null;

    token: string | null;
    login: (user: { name: string; email: string }, token: string) => void;
    logout: () => void;
}

const AuthContext = createContext<AuthContextType|null>(null);

export const AuthProvider = ({ children }: { children: React.ReactNode }) => {

    const [isAuthenticated, setIsAuthenticated] = useState(
        localStorage.getItem("token") !== null && localStorage.getItem("user") !== null
    );
    const [user, setUser] = useState<AuthContextType["user"]>(
        localStorage.getItem("user") ? 
        JSON.parse(localStorage.getItem("user")!) : null);
        
    const [token, setToken] = useState<string | null>(localStorage.getItem("token"));

    const login = (user: { name: string; email: string }, token: string) => {
        setUser(user);
        setToken(token);
        setIsAuthenticated(true);
        localStorage.setItem("token", token);
        localStorage.setItem("user", JSON.stringify(user));
    };

    const logout = () => {
        setUser(null);
        setToken(null);
        setIsAuthenticated(false);
        localStorage.removeItem("token");
        localStorage.removeItem("user");
    };

    return (
        <AuthContext.Provider value={{ isAuthenticated, user, token, login, logout }}>
            {children}
        </AuthContext.Provider>
    );
}

export const useAuth = () => {
    const context = useContext(AuthContext);
    if (!context) {
        throw new Error("useAuth must be used within an AuthProvider");
    }
    return context;
}