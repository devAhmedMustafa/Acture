import { useParams } from "react-router-dom";
import useRoomWebSocket from "../hooks/useRoomWebSocket";
import { useEffect } from "react";

export default function RoomPage() {

    const { roomId } = useParams<{ roomId: string }>();
    const { messages, sendMessage } = useRoomWebSocket(roomId!);

    useEffect(() => {
        if (!roomId) {
            console.error("Room ID is required to connect to the WebSocket.");
            return;
        }
        console.log(`Connected to room: ${roomId}`);
    }, [roomId]);

    return (
        <div>
            <h1>Room Page</h1>
            <p>This is the room page where users can interact with the room.</p>

            <div className="messages">
                <h2>Messages:</h2>
                <ul>
                    {messages.map((msg, index) => (
                        <li key={index}>{msg}</li>
                    ))}
                </ul>
            </div>

            <div className="send-message">
                <h2>Send a Message:</h2>
                <input
                    type="text"
                    placeholder="Type your message here"
                    onKeyDown={(e) => {
                        if (e.key === 'Enter') {
                            sendMessage((e.target as HTMLInputElement).value);
                            (e.target as HTMLInputElement).value = '';
                        }
                    }}
                    className="border border-gray-300 p-2 rounded w-full"
                />
            </div>
        </div>
    );
}