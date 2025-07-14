import { Icon } from "@iconify/react/dist/iconify.js";
import { useState } from "react";

export default function MCQScreen({question, options, handleAction}
    : {question: string, options: string[], handleAction?: (option: number) => Promise<void>}) {
    
    const [chosenOption, setChosenOption] = useState<number | null>(null);

    const handleOptionClick = (index: number) => {
        if (handleAction) {
            try {
                handleAction(index).then(() => {
                    setChosenOption(index);
                });
            }
            catch (error) {
                console.error("Error handling option click:", error);
            }
        }

    };

    return (
        
        <div className="w-full h-full flex flex-col justify-center items-center p-4 gap-5">

            <h2 className="hidden">Multiple Choice Question</h2>
            
            {
                chosenOption == null ?
                <>
                    <p className="text-2xl font-semibold">{question}</p>
                    <ul className="flex gap-2">
                        {options.map((option, index) => (
                            <button
                                className="bg-major px-4 py-2 rounded hover:bg-hover transition-colors"
                                key={index} onClick={() => handleOptionClick(index)}>
                                <li key={index}>{option}</li>
                            </button>
                        ))}
                    </ul>

                </>
                :
                <div className="text-2xl font-semibold">
                    <p>You selected: {options[chosenOption]}</p>
                    <Icon icon="material-symbols:check-circle-outline" className="inline-block text-3xl text-green-500" />
                </div>
            }

        </div>
    );
}