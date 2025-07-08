import { useEffect, useRef, useState } from "react";

interface SignalMessage {
  type: string;
  from: string;
  to?: string;
  payload: any;
}

export function useVoiceMesh(
  sendMessage: (msg: SignalMessage) => void,
  messages: SignalMessage[],
  selfId: string
) {
  const peers = useRef<Record<string, RTCPeerConnection>>({});
  const iceBuffers = useRef<Record<string, RTCIceCandidate[]>>({});

  const [muted, setMuted] = useState(false);
  const [localStream, setLocalStream] = useState<MediaStream | null>(null);
  const [remoteStreams, setRemoteStreams] = useState<MediaStream[]>([]);

  useEffect(() => {
    navigator.mediaDevices.getUserMedia({ audio: true })
      .then(stream => {
        setLocalStream(stream);
      })
      .catch(console.error);
  }, []);

  const sendAndLog = (msg: SignalMessage) => {
    console.log("Sending:", msg);
    sendMessage(msg);
  };

  const closePeer = (peerId: string) => {
    const pc = peers.current[peerId];
    if (pc) {
      pc.close();
      delete peers.current[peerId];
      delete iceBuffers.current[peerId];
    }
  };

  const createPeer = async (peerId: string, isInitiator: boolean) => {
    if (peers.current[peerId]) return peers.current[peerId];

    const pc = new RTCPeerConnection();
    peers.current[peerId] = pc;
    iceBuffers.current[peerId] = [];

    pc.onicecandidate = e => {
      if (e.candidate) {
        sendAndLog({ type: "voice-ice", from: selfId, to: peerId, payload: e.candidate });
      }
    };

    pc.ontrack = e => {
      const [stream] = e.streams;
      setRemoteStreams(prev => {
        if (!prev.some(s => s.id === stream.id)) {
          return [...prev, stream];
        }
        return prev;
      });
    };

    if (localStream) {
      localStream.getTracks().forEach(track => pc.addTrack(track, localStream));
    }

    if (isInitiator && localStream) {
      const offer = await pc.createOffer();
      await pc.setLocalDescription(offer);
      sendAndLog({ type: "voice-offer", from: selfId, to: peerId, payload: offer });
    }

    return pc;
  };

  useEffect(() => {
    messages.forEach(async msg => {
      const { type, from, to, payload } = msg;
      if (from === selfId || (to && to !== selfId)) return;

      let pc = peers.current[from];
      const isInitiator = selfId < from;

      if (type === "hello") {
        if (!pc) {
          console.log("New peer connected:", from, "Is initiator:", isInitiator);
          pc = await createPeer(from, isInitiator);
        }
      }

      if (type === "voice-offer") {
        if (!pc) pc = await createPeer(from, false);
        console.log("Received voice-offer from peer:", from);

        try {
          if (!pc.remoteDescription) {
            await pc.setRemoteDescription(new RTCSessionDescription(payload));
            const answer = await pc.createAnswer();
            await pc.setLocalDescription(answer);
            sendAndLog({ type: "voice-answer", from: selfId, to: from, payload: answer });

            // Apply any buffered ICE
            (iceBuffers.current[from] || []).forEach(async candidate => {
              try { await pc.addIceCandidate(candidate); } catch (e) { console.error(e); }
            });
            iceBuffers.current[from] = [];
          } else {
            console.warn("Ignoring duplicate offer from", from);
          }
        } catch (err) {
          console.error("Error in voice-offer:", err);
          closePeer(from);
        }
      }

      if (type === "voice-answer") {
        if (!pc || !payload) return;

        try {
          if (pc.signalingState === "have-local-offer") {
            await pc.setRemoteDescription(new RTCSessionDescription(payload));
            (iceBuffers.current[from] || []).forEach(async candidate => {
              try { await pc.addIceCandidate(candidate); } catch (e) { console.error(e); }
            });
            iceBuffers.current[from] = [];
          } else {
            console.warn("Remote description already set or invalid state for:", from);
          }
        } catch (err) {
          console.error("Error in voice-answer:", err);
          closePeer(from);
        }
      }

      if (type === "voice-ice") {
        if (!pc) {
          iceBuffers.current[from] = iceBuffers.current[from] || [];
          iceBuffers.current[from].push(new RTCIceCandidate(payload));
        } else if (pc.remoteDescription) {
          try {
            await pc.addIceCandidate(new RTCIceCandidate(payload));
          } catch (err) {
            console.error("Error adding ICE candidate:", err);
          }
        } else {
          iceBuffers.current[from].push(new RTCIceCandidate(payload));
        }
      }
    });
  }, [messages, localStream]);

  const toggleMute = () => {
    if (localStream) {
      const enabled = !muted;
      localStream.getAudioTracks().forEach(track => (track.enabled = enabled));
      setMuted(!muted);
    }
  };

  const announcePresence = () => {
    sendAndLog({ type: "hello", from: selfId, payload: {} });
  };

  return { muted, toggleMute, announcePresence, remoteStreams };
}
