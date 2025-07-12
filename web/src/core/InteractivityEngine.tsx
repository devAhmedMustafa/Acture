import { useEffect, useState } from "react";
import { useSocketContext } from "../contexts/SocketContext";
import StationMapper from "../mappers/StationMapper";
import { Station } from "../types/Station";
import api from "../utils/api";

export default function InteractivityEngine() {

    const { messages, room } = useSocketContext();
    const [currentInteractivity, setCurrentInteractivity] = useState<Station|null>(null);

    const takeAction = async (thread: number) => {
        try{
            const res = await api.post(`/${room}/traverse`, {
                thread: thread,
            })

            if (res.status !== 200) {
                throw new Error("Failed to take action on interactivity");
            }
            
        }
        catch (error) {
            console.error("Error taking action on interactivity:", error);
        }
    }

    useEffect(()=>{
        const interactivityMessages = messages.filter(m => m.type === "interactivity");
        if (interactivityMessages.length === 0) return;

        const currentInteractivity = interactivityMessages[interactivityMessages.length - 1].payload;
        const interactivity = StationMapper.getFromType(currentInteractivity, currentInteractivity.station_type);

        setCurrentInteractivity(interactivity);
        
    }, [messages])

    return {
        currentInteractivity,
        takeAction
    }

}