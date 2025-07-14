import { Icon } from "@iconify/react/dist/iconify.js";
import { MeetingState, useMeetingContext } from "../contexts/MeetingContext";
import { useSocketContext } from "../contexts/SocketContext";
import api from "../utils/api";

export default function MoveMediaButton() {

    const { room } = useSocketContext();
    const { setMeetingState } = useMeetingContext();

    const handleClick = async () => {
        try {
            const response = await api.get(`rooms/${room}/move`);
            if (response.status !== 200) {
                throw new Error("Failed to move media");
            }
            setMeetingState(MeetingState.MEDIA);
        } catch (error) {
            console.error("Error moving media:", error);
        }
    }

    return (
        <button onClick={handleClick} className="bg-accent text-white size-12 rounded-full hover:bg-hover flex justify-center items-center">
            <Icon icon="fluent:next-24-regular" className="inline-block text-2xl" />
        </button>
    );

}

