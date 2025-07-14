import { useEffect, useState } from "react";
import { useSocketContext } from "../contexts/SocketContext";
import StationMapper from "../mappers/StationMapper";
import { Station } from "../types/Station";
import api from "../utils/api";
import { useAuth } from "../contexts/AuthContext";

export default function InteractivityEngine() {

    const { messages, room } = useSocketContext();
    const [currentInteractivity, setCurrentInteractivity] = useState<Station|null>(null);
    const { token } = useAuth();

    const messagesChecked : any[] = messages;

    const takeAction = async (thread: number) => {
        try{
            const formData = new FormData();
            formData.append("thread", thread.toString());
            const res = await api.post(`/rooms/${room}/traverse`, formData, {
                headers: {
                    "Content-Type": "multipart/form-data",
                    Authorization: `Bearer ${token}`,
                },
            })

            if (res.status !== 200) {
                throw new Error("Failed to take action on interactivity");
            }
            
            setTimeout(()=> {
                setCurrentInteractivity(null);
            }, 2000);
        }
        catch (error) {
            console.error("Error taking action on interactivity:", error);
        }
    }

    useEffect(()=>{
        const interactivityMessages = messages.filter(m => m.type === "interactivity");
        if (interactivityMessages.length === 0) return;

        const currentInteractivity = interactivityMessages[interactivityMessages.length - 1].payload;
        if (messagesChecked.includes(currentInteractivity)) return;
        messagesChecked.push(currentInteractivity);

        console.log("Current interactivity:", currentInteractivity);

        if (!currentInteractivity) {
            setCurrentInteractivity(null);
            return;
        }

        const interactivity = StationMapper.getFromType(currentInteractivity, currentInteractivity.station_type);

        setCurrentInteractivity(interactivity);
        
    }, [messages])

    return {
        currentInteractivity,
        takeAction
    }

}