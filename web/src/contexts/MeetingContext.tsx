export enum MeetingState {
    MEDIA, INTERACTION
}

import { createContext, useContext, useState } from "react";

interface MeetingContextType {
    meetingState: MeetingState;
    setMeetingState: (state: MeetingState) => void;
}

const MeetingContext = createContext<MeetingContextType | undefined>(undefined);

export const MeetingProvider: React.FC<{ children: React.ReactNode }> = ({ children }) => {
    const [meetingState, setMeetingState] = useState<MeetingState>(MeetingState.MEDIA);
    return (
        <MeetingContext.Provider value={{ meetingState, setMeetingState }}>
            {children}
        </MeetingContext.Provider>
    );
};

export const useMeetingContext = (): MeetingContextType => {
    const context = useContext(MeetingContext);
    if (!context) {
        throw new Error("useMeetingContext must be used within a MediaProvider");
    }
    return context;
};

export default MeetingContext;