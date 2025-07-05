import { useEffect, useRef, useState } from "react";
import { useRoomContext } from "../context/RoomContext";

export default function useRoomWebSocket(targetRoomId: string) {

    const ws = useRef<WebSocket | null>(null);
    const [messages, setMessages] = useState<string[]>([]);
    const { setRoomId } = useRoomContext();

    useEffect(() => {

        if (!targetRoomId) return;

        ws.current = new WebSocket(`ws://localhost:8000/ws/room/${targetRoomId}`);

        ws.current.onopen = () => {
            console.log("WebSocket connection established");
            setRoomId(targetRoomId);
        }

        ws.current.onmessage = (event) => {
            const message = event.data;
            setMessages((prev) => [...prev, message]);
        }

        ws.current.onclose = () => {
            console.log("WebSocket connection closed");
        }

        return () => {
            ws.current?.close();
        };

    }, [targetRoomId])

    const sendMessage = (message: string) => {
        if (ws.current && ws.current.readyState === WebSocket.OPEN) {
            ws.current.send(message);
        }
    }

    return { messages, sendMessage };

}