import { useEffect, useRef, useState } from "react";
import { MeetingRole, useRoomContext } from "../context/RoomContext";

export function useAutoVoice(roomId: string, sendMessage: (message: any) => void, messages: any[]) {
    const { role } = useRoomContext();
    console.log("useAutoVoice initialized with roomId:", roomId, "and role:", role);
    const peer = useRef<RTCPeerConnection | null>(null);
    const [muted, setMuted] = useState(false);
    const [stream, setStream] = useState<MediaStream | null>(null);
    const iceCandidatesBuffer = useRef<any[]>([]);

    const localStreamRef = useRef<MediaStream | null>(null);
    const audioRef = useRef<HTMLAudioElement>(new Audio());

    useEffect(() => {
        if (!roomId) return;

        let isActive = true;

        if (peer.current) {
            peer.current.close();
        }

        const pc = new RTCPeerConnection();
        peer.current = pc;

        audioRef.current.autoplay = true;

        pc.onicecandidate = e => {
            if (e.candidate) sendMessage({ type: "voice-ice", payload: e.candidate });
        };

        pc.ontrack = e => {
            audioRef.current.srcObject = e.streams[0];
            audioRef.current.play().catch(console.error);
        };

        navigator.mediaDevices.getUserMedia({ audio: true }).then(localStream => {
            if (!isActive) return;  // Abort if effect is no longer active

            localStreamRef.current = localStream;

            if (pc.signalingState !== "closed") {
                localStream.getTracks().forEach(track => pc.addTrack(track, localStream));
            }

            if (role === MeetingRole.HOST && pc.signalingState === "stable") {
                pc.createOffer().then(offer => {
                    pc.setLocalDescription(offer);
                    sendMessage({ type: "voice-offer", payload: offer });
                });
            }
        }).catch(console.error);

        return () => {
            isActive = false;
            pc.close();
            localStreamRef.current?.getTracks().forEach(track => track.stop());
            audioRef.current.srcObject = null;
        };

    }, [roomId]);



    useEffect(() => {
        if (!peer.current || messages.length === 0) return;

        const pc = peer.current;
        const msg = messages[messages.length - 1];

        (async () => {
            if (msg.type === "voice-offer" && role !== MeetingRole.HOST) {
                await pc.setRemoteDescription(new RTCSessionDescription(msg.payload));
                const answer = await pc.createAnswer();
                await pc.setLocalDescription(answer);
                sendMessage({ type: "voice-answer", payload: answer });

                // Apply buffered ICE candidates
                iceCandidatesBuffer.current.forEach(candidate => pc.addIceCandidate(candidate));
                iceCandidatesBuffer.current = [];

                console.log("Voice offer received, answer sent.");
            }

            if (msg.type === "voice-answer" && role === MeetingRole.HOST) {
                await pc.setRemoteDescription(new RTCSessionDescription(msg.payload));
                iceCandidatesBuffer.current.forEach(candidate => pc.addIceCandidate(candidate));
                iceCandidatesBuffer.current = [];
                console.log("Voice answer received.");
            }

            if (msg.type === "voice-ice") {
                const candidate = new RTCIceCandidate(msg.payload);
                if (pc.remoteDescription && pc.remoteDescription.type) {
                    await pc.addIceCandidate(candidate);
                } else {
                    iceCandidatesBuffer.current.push(candidate);
                }
            }
        })();
    }, [messages]);

    const toggleMute = () => {
        if (stream) {
            const enabled = !muted;
            stream.getAudioTracks().forEach(track => (track.enabled = enabled));
            setMuted(!muted);
        }
    };

    return { muted, toggleMute };
}
