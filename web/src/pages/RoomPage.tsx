import { useParams } from "react-router-dom";
import { useEffect } from "react";
import ChatPanel from "../components/ChatPanel";
import {SocketProvider} from "../contexts/SocketContext";
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

    return (
        <SocketProvider targetRoomId={roomId!}>
            <div className="grid grid-cols-1 md:grid-cols-4 h-screen bg-bg-primary">

                <div className="col-span-1 md:col-span-3">
                    <MediaRenderer/>
                    <InteractivityRenderer/>
                    <TriggerStationButton/>

                </div>

                <div className="col-span-1 md:col-span-1">
                    <ChatPanel />
                </div>


                    
            </div>
        </SocketProvider>
    );
}