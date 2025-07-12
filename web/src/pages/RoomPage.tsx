import { useParams } from "react-router-dom";
import { useEffect } from "react";
import ChatPanel from "../components/ChatPanel";
import {SocketProvider} from "../contexts/SocketContext";
import api from "../utils/api";
import MediaRenderer from "../core/MediaRenderer";
import InteractivityRenderer from "../core/InteractivityRenderer";
import TriggerStationButton from "../components/TriggerStationButton";

export default function RoomPage() {

    const { roomId } = useParams<{ roomId: string }>();

    useEffect(() => {
        if (!roomId) {
            console.error("Room ID is required to connect to the WebSocket.");
            return;
        }
    }, [roomId]);

    async function getCurrentMedia() {
        try {
            const res = await api.get(`/rooms/${roomId}/media`);

            if (res.status !== 200) {
                throw new Error("Failed to fetch current media");
            }
            
            const curentMedia = res.data.current_media;

            console.log("Current Media:", curentMedia);
        } catch (error) {
            console.error("Error fetching current media:", error);
            alert("Failed to fetch current media. Please try again.");
        }
    }

    return (
        <SocketProvider targetRoomId={roomId!}>
            <div>
                <h1>Room Page</h1>
                <p>This is the room page where users can interact with the room.</p>

                <ChatPanel roomId={roomId!} />

                <div>
                    <button onClick={getCurrentMedia}>Get current media</button>
                </div>

                <MediaRenderer/>
                <InteractivityRenderer/>
                <TriggerStationButton/>
                    
            </div>
        </SocketProvider>
    );
}