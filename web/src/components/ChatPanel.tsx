import { useState } from "react";

export default function ChatPanel({ roomId, messages, sendMessage }: { roomId: string , messages: any[], sendMessage: (message: any) => void }) {
  const [input, setInput] = useState("");

  const handleSend = () => {
    if (input.trim() === "") return;
    sendMessage({ type: "chat", payload: { sender: "You", text: input } });
    setInput("");
  };

  return (
    <div className="p-4 border rounded-lg max-w-md mx-auto bg-white shadow">
      <h2 className="text-lg font-semibold mb-2">Room: {roomId}</h2>
      <div className="h-48 overflow-y-auto border p-2 mb-2 rounded bg-gray-100 text-sm">
        {messages
          .filter((m) => m.type === "chat")
          .map((msg, i) => (
            <div key={i} className="mb-1">
              <strong>{msg.payload.sender}:</strong> {msg.payload.text}
            </div>
          ))}
      </div>
      <div className="flex gap-2">
        <input
          type="text"
          className="flex-1 border rounded p-1"
          placeholder="Type message"
          value={input}
          onChange={(e) => setInput(e.target.value)}
          onKeyDown={(e) => e.key === "Enter" && handleSend()}
        />
        <button
          onClick={handleSend}
          className="bg-blue-600 text-white px-3 py-1 rounded"
        >
          Send
        </button>
      </div>
    </div>
  );
}
