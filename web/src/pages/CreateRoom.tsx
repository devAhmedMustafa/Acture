import { useState } from "react";
import api from "../utils/api";
import { useNavigate } from "react-router-dom";
import { MeetingRole, useRoomContext } from "../context/RoomContext";

interface RoomData {
    room_id: string;
}

export default function CreateRoom() {
    
    const [file, setFile] = useState<File | null>(null);
    const [roomData, setRoomData] = useState<RoomData|null>(null);
    const {setRole} = useRoomContext();
    const [loading, setLoading] = useState(false);
    const navigate = useNavigate();

    const handleFileChange = (e: any)=> {
        const selectedFile = e.target.files?.[0];
        if (selectedFile) {
            setFile(selectedFile);
        }
    }

    const handleSubmit = async (e: any) => {
        e.preventDefault();
        if (!file) {
            alert("Please select a file to upload.");
            return;
        }

        setLoading(true);
        const formData = new FormData();
        formData.append("spi_file", file);

        try {
            const response = await api.post("/host", formData, {
                headers: {
                    "Content-Type": "multipart/form-data",
                },
            });

            setRoomData(response.data);
            setRole(MeetingRole.HOST);
            navigate(`/room/${response.data.room_id}`);
        }
        catch (error) {
            console.error("Error creating room:", error);
            alert("Failed to create room. Please try again.");
        }
        finally {
            setLoading(false);
        }
    }

    return (
        <div className="max-w-md mx-auto mt-10 p-6 bg-white rounded-2xl shadow-lg space-y-4">
        <h2 className="text-2xl font-bold text-center">Create a New Room</h2>

        <form onSubmit={handleSubmit} className="space-y-4">
            <input
            type="file"
            accept=".spi"
            onChange={handleFileChange}
            className="border border-gray-300 p-2 rounded w-full"
            />

            <button
            type="submit"
            disabled={loading}
            className="w-full bg-blue-600 text-white py-2 rounded hover:bg-blue-700 transition"
            >
            {loading ? "Creating..." : "Create Room"}
            </button>
        </form>

        {roomData && (
            <div className="bg-gray-100 p-4 rounded mt-4 text-center">
            <p className="font-semibold">Room Created!</p>
            <p className="break-all">{roomData.room_id}</p>
            </div>
        )}

        </div>
    );

}