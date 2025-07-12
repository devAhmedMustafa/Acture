import { useState } from "react";
import { useAuth } from "../contexts/AuthContext";
import { useSocketContext } from "../contexts/SocketContext";
import { Icon } from "@iconify/react"
import ChatMessage from "./containers/ChatMessage";

export default function ChatPanel() {
  const [input, setInput] = useState("");
  const { user } = useAuth();
  const {messages, sendMessage} = useSocketContext();

  const handleSend = () => {
    if (input.trim() === "") return;

    sendMessage({ type: "chat", payload: { sender: user?.email, text: input } });
    setInput("");
  };

  return (
    <div className="p-4 h-full shadow flex flex-col justify-end-safe">
      
      <div className="h-full overflow-y-auto p-2 mb-2 text-sm">
        {messages
          .filter((m) => m.type === "chat")
          .map((msg, i) => (
            <ChatMessage key={i} message={msg.payload}/>
          ))}
      </div>

      <div className="flex gap-2 border border-border py-2 px-4 rounded-xl">
        <input
          type="text"
          className="flex-1 focus:outline-none"
          placeholder="Type message..."
          value={input}
          onChange={(e) => setInput(e.target.value)}
          onKeyDown={(e) => e.key === "Enter" && handleSend()}
        />
        <button
          onClick={handleSend}
          className="bg-accent text-white p-2 rounded-full flex justify-center items-center"
        >
          <Icon icon="tabler:send" className="text-xl"/>
        </button>
      </div>
    </div>
  );
}
