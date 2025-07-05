import { useState } from "react";
import { Link } from "react-router-dom";

export default function HomePage() {

    const [roomId, setRoomId] = useState<string | null>(null);


    return (
        <div className="flex flex-col items-center justify-center h-screen bg-gray-100">
            <h1 className="text-4xl font-bold mb-4">Welcome to Acture</h1>
            <p className="text-lg mb-8">Your collaborative platform for interactive experiences.</p>
            <Link to="/host" className="px-6 py-3 bg-blue-600 text-white rounded hover:bg-blue-700 transition">
                Create a Room
            </Link>

            <div className="mt-8">
                <input
                    type="text"
                    placeholder="Enter Room ID"
                    value={roomId || ""}
                    onChange={(e) => setRoomId(e.target.value)}
                    className="border border-gray-300 p-2 rounded w-64"
                />
                <Link
                    to={`/room/${roomId}`}
                    className="ml-2 px-4 py-2 bg-green-600 text-white rounded hover:bg-green-700 transition"
                >
                    Join Room
                </Link>
            </div>
            
        </div>
    );

}