import StationType from "../enums/StationType";

export interface Station {
    
    stationType: StationType;
    willPause: boolean;
    lifetime: number;

    fromJson(json: any) : void;
}

export class MCQStation implements Station {
    

    stationType: StationType;
    willPause: boolean;
    lifetime: number;
    question: string;
    options: string[];

    constructor(){
        this.stationType = StationType.MCQ;
        this.willPause = false;
        this.lifetime = 0;
        this.question = "";
        this.options = [];
    }

    fromJson(json: any) {
        this.stationType = json.station_type;
        this.willPause = json.will_pause;
        this.lifetime = json.lifetime;
        this.question = json.question;
        this.options = json.options || [];
    }
}
