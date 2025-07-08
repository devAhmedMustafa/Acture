import { useParams } from "react-router-dom";
import { useEffect, useMemo, useRef } from "react";
import ChatPanel from "../components/ChatPanel";
import useRoomWebSocket from "../hooks/useRoomWebSocket";
import { useVoiceMesh } from "../hooks/useVoiceMesh";
import { v4 } from "uuid";

export default function RoomPage() {

    const { roomId } = useParams<{ roomId: string }>();
    const {sendMessage, messages, ready} = useRoomWebSocket(roomId!);
    const selfId = useMemo(() => v4(), []);
    // const { muted, toggleMute, announcePresence, remoteStreams } = useVoiceMesh(sendMessage, messages, selfId);

    // For remote audio refs
    const audioRefs = useRef<Record<string, HTMLAudioElement | null>>({});

    useEffect(() => {
        if (!roomId) {
            console.error("Room ID is required to connect to the WebSocket.");
            return;
        }
        if (!ready) return;
        console.log(`Connected with : ${selfId}`);
        // announcePresence();
    }, [roomId, ready]);

    // useEffect(() => {
    //     // Set srcObject for each remote stream
    //     remoteStreams.forEach((stream) => {
    //         const audioEl = audioRefs.current[stream.id];
    //         if (audioEl && audioEl.srcObject !== stream) {
    //             audioEl.srcObject = stream;
    //         }
    //     });
    // }, [remoteStreams]);

    return (
        <div>
            <h1>Room Page</h1>
            <p>This is the room page where users can interact with the room.</p>

            <ChatPanel roomId={roomId!} messages={messages} sendMessage={sendMessage} />

            {/* <div className="mt-4 text-center">
                <button
                    onClick={toggleMute}
                    className={`px-4 py-2 rounded ${muted ? 'bg-red-600' : 'bg-green-600'} text-white`}
                >
                    {muted ? "Unmute" : "Mute"}
                </button>
            </div> */}

            {/* Render remote audio streams */}
            <div>
                {/* {remoteStreams.map((stream) => (
                    <audio
                        key={stream.id}
                        ref={el => { audioRefs.current[stream.id] = el; }}
                        autoPlay
                        controls
                    />
                ))} */}
            </div>
                
        </div>
    );
}