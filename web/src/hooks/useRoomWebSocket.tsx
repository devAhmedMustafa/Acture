import { useEffect, useRef, useState } from "react";
import { useRoomContext } from "../context/RoomContext";

export default function useRoomWebSocket(targetRoomId: string) {

    const ws = useRef<WebSocket | null>(null);
    const [messages, setMessages] = useState<any[]>([]);
    const { setRoomId } = useRoomContext();
    const [ready, setReady] = useState(false);

    useEffect(() => {

        if (!targetRoomId) return;

        ws.current = new WebSocket(`ws://localhost:8000/ws/room/${targetRoomId}`);

        ws.current.onopen = () => {
            setRoomId(targetRoomId);
            setReady(true);
        }

        ws.current.onmessage = (event) => {
            const message = JSON.parse(event.data);
            setMessages((prev) => [...prev, message]);
        }

        ws.current.onerror = (err) => {};

        ws.current.onclose = (event) => {
            setReady(false);
        }

        return () => {
            ws.current?.close();
        };

    }, [targetRoomId])

    const sendMessage = (message: any) => {
        if (ws.current && ws.current.readyState === WebSocket.OPEN) {
            ws.current.send(JSON.stringify(message));
        }
    }

    return { messages, sendMessage, ready };

}