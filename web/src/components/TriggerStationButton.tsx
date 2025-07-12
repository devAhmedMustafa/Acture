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
        <button onClick={handleClick} className="bg-blue-500 text-white px-4 py-2 rounded hover:bg-blue-600">
            Trigger Station
        </button>
    );

}
