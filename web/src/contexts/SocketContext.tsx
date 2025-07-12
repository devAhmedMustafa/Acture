import React, { createContext, useState, useRef, useEffect, useContext } from "react";
import { useAuth } from "./AuthContext";

export interface SocketContextProps {
    messages: any[];
    sendMessage: (message: any) => void;
    ready: boolean;
    room: string | null;
}

const SocketContext = createContext<SocketContextProps | undefined>(undefined);

export const SocketProvider: React.FC<{ children: React.ReactNode, targetRoomId: string }> = ({ children, targetRoomId }) => {

    const ws = useRef<WebSocket | null>(null);

    const [messages, setMessages] = useState<any[]>([
        { type: "chat", payload: { sender: "System", text: "Welcome to the chat!" } },
        { type: "chat", payload: { sender: "System", text: "Feel free to send messages." } }
    ]);
    const [room, setRoom] = useState<string | null>(null);
    const [ready, setReady] = useState(false);
    const {user} = useAuth();

    const sendMessage = (message: any) => {
        if (ws.current && ws.current.readyState === WebSocket.OPEN) {
            ws.current.send(JSON.stringify(message));
        }
    }

    useEffect(() => {
    
        if (!targetRoomId) return;

        ws.current = new WebSocket(`ws://localhost:8000/rooms/join/${targetRoomId}?client_id=${user?.email}`);

        ws.current.onopen = () => {
            setRoom(targetRoomId);
            setReady(true);
            console.log("WebSocket connection established for room:", targetRoomId);
        }

        ws.current.onmessage = (event) => {
            const message = JSON.parse(event.data);
            setMessages((prev) => [...prev, message]);
        }

        ws.current.onerror = (err) => {
            console.error("WebSocket error:", err);
        };

        ws.current.onclose = () => {
            setReady(false);
        }

        return () => {
            ws.current?.close();
        };

    }, [targetRoomId])

    return (
        <SocketContext.Provider value={{ messages, sendMessage, ready, room }}>
            {children}
        </SocketContext.Provider>
    );

}

export const useSocketContext = (): SocketContextProps => {
    const context = useContext(SocketContext);
    if (!context) {
        throw new Error("useSocketContext must be used within a SocketProvider");
    }
    return context;
}