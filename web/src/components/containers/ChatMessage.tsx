import { Icon } from "@iconify/react/dist/iconify.js";
import { useAuth } from "../../contexts/AuthContext";

export default function ChatMessage({ message }: { message: { sender: string, text: string } }) {

    const {user} = useAuth();

    return (
        <div className="flex items-start gap-2 mb-2 p-1">

            {user?.email !== message.sender && (
                <>
                <div className="flex items-center">
                    <Icon icon="material-symbols-light:family-star" className="text-4xl text-accent"/>
                </div>
                
                <div className="flex flex-col gap-2">
                    <div className="text-[16px]">
                        <span className="font-semibold">{message.sender}</span>
                    </div>
                    <div className="text-sm bg-bg-tertiary border-border border-1 px-4 py-2 rounded-full">
                        {message.text}
                    </div>
                </div>
                </>
            )}

            {user?.email === message.sender && (
                <>
                <div className="flex flex-col w-full items-end gap-1">
                    <div className="text-sm bg-accent text-white px-4 py-2 rounded-full">
                        {message.text}
                    </div>
                </div>
                </>
            )}
            

        </div>
    );

}