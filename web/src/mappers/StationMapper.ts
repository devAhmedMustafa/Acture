import StationType from "../enums/StationType";
import { MCQStation, Station } from "../types/Station";

export default class StationMapper {

    static getFromType(data: any, type: StationType): Station {

        if (!data || !type) {
            console.error("Invalid data or type provided to Station.getFromType");
        }

        switch (type) {
            case StationType.MCQ:
                const mcq = new MCQStation();
                mcq.fromJson(data);
                return mcq;

            case StationType.HISTORY:
                throw new Error("History interactivity type is not yet implemented");

            default:
                throw new Error(`Unsupported station type: ${type}`);
        }
    }

}