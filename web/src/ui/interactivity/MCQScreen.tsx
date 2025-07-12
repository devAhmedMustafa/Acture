export default function MCQScreen({question, options, handleAction}: {question: string, options: string[], handleAction?: (option: number) => void}) {
    return (
        <div>
            <h2>Multiple Choice Question</h2>
            <p>{question}</p>
            <ul>
                {options.map((option, index) => (
                    <button key={index} onClick={() => handleAction && handleAction(index)}>
                        <li key={index}>{option}</li>
                    </button>
                ))}
            </ul>
        </div>
    );
}