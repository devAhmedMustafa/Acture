import { useParams } from "react-router-dom";
import { useEffect } from "react";
import ChatPanel from "../components/ChatPanel";
import {SocketProvider} from "../contexts/SocketContext";
import MediaRenderer from "../core/MediaRenderer";
import InteractivityRenderer from "../core/InteractivityRenderer";
import TriggerStationButton from "../components/TriggerStationButton";
import MoveMediaButton from "../components/MoveMediaButton";

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
            <div className="grid grid-cols-1 md:grid-cols-4 h-screen bg-gradient-to-tr from-bg-primary to-[#281d3a]">

                <div className="col-span-1 md:col-span-3 grid grid-rows-8 gap-4 p-8">

                    <div className="row-span-1 flex gap-3 items-center justify-center border-b border-border">
                        <TriggerStationButton/>
                        <MoveMediaButton/>
                    </div>

                    <div className="row-span-6 relative">
                        <InteractivityRenderer/>
                        <MediaRenderer/>
                    </div>

                    <div className="row-span-1">

                    </div>
                </div>

                <div className="col-span-1 md:col-span-1 bg-bg-primary rounded-bl-4xl rounded-tl-4xl p-4">
                    <ChatPanel />
                </div>


                    
            </div>
        </SocketProvider>
    );
}