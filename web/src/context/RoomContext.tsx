import React, { createContext, ReactNode, useState, useContext } from "react";

interface RoomContextType {
    roomId: string | null;
    setRoomId: (id: string | null) => void;
}

const RoomContext = createContext<RoomContextType | undefined>(undefined);

export const RoomProvider: React.FC<{ children: ReactNode }> = ({ children }) => {
    const [roomId, setRoomId] = useState<string | null>(null);
    
    return (
        <RoomContext.Provider value={{ roomId, setRoomId }}>
            {children}
        </RoomContext.Provider>
    );
}

export const useRoomContext = (): RoomContextType => {
    const context = useContext(RoomContext);
    if (!context) {
        throw new Error("useRoomContext must be used within a RoomProvider");
    }
    return context;
}