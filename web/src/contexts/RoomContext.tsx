import React, { createContext, ReactNode, useState, useContext } from "react";

export enum MeetingRole {
    HOST,
    PARTICIPANT,
    OBSERVER
}

interface RoomContextType {
    roomId: string | null;
    setRoomId: (id: string | null) => void;
    role: MeetingRole;
    setRole: (role: MeetingRole) => void;
}

const RoomContext = createContext<RoomContextType | undefined>(undefined);

export const RoomProvider: React.FC<{ children: ReactNode }> = ({ children }) => {
    const [roomId, setRoomId] = useState<string | null>(null);
    const [role, setRole] = useState<MeetingRole>(MeetingRole.PARTICIPANT);
    
    return (
        <RoomContext.Provider value={{ roomId, setRoomId, role, setRole }}>
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