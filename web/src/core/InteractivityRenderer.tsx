import StationType from "../enums/StationType";
import { MCQStation } from "../types/Station";
import MCQScreen from "../ui/interactivity/MCQScreen";
import InteractivityEngine from "./InteractivityEngine";

export default function InteractivityRenderer() {
    const { currentInteractivity, takeAction } = InteractivityEngine();

    if (!currentInteractivity) return;

    switch (currentInteractivity?.stationType) {
        case StationType.MCQ:
            const mcq = currentInteractivity as MCQStation;
            return (
                <div className="absolute inset-0 w-full h-full bg-bg-primary">
                    <MCQScreen question={mcq.question} options={mcq.options} handleAction={takeAction} />
                </div>
            );

        default:
            return <div>No interactivity available</div>;
    }
}