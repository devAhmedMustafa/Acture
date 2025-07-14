import { Icon } from "@iconify/react/dist/iconify.js";
import { useSocketContext } from "../contexts/SocketContext";
import api from "../utils/api";

export default function TriggerStationButton() {

    const {room} = useSocketContext();

    const handleClick = async () => {
        try {
            const response = await api.get(`rooms/${room}/trigger_station`);
            if (response.status !== 200) {
                throw new Error("Failed to trigger station");
            }
        }
        catch (error) {
            console.error("Error triggering station:", error);
        }
    }

    return (
        <button onClick={handleClick} className="bg-accent text-white size-12 rounded-full hover:bg-hover flex justify-center items-center">
            <Icon icon="material-symbols-light:interactive-space-outline" className="inline-block text-3xl" />
        </button>
    );

}
