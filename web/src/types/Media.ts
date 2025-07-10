import MediaType from "../enums/MediaType";

export interface Media {
    mediaPath: string;
    mediaType: MediaType;

    fromJson(json: any) : void;
}

export class Video implements Media {
    mediaPath: string;
    mediaType: MediaType;
    start: number;
    end: number;

    constructor(){
        this.mediaPath = "";
        this.mediaType = MediaType.VIDEO;
        this.start = 0;
        this.end = 0;
    }

    fromJson(json: any) {
        this.mediaPath = json.media_path;
        this.mediaType = json.media_type;
        this.start = json.start;
        this.end = json.end;
    }
}
