import MediaType from "../enums/MediaType";
import { Media, Video } from "../types/Media";

export default class MediaMapper {

    static getFromType(data: any, type: MediaType): Media {

        if (!data || !type) {
            console.error("Invalid data or type provided to MediaMapper.getFromType");
        }

        switch (type) {
            case MediaType.VIDEO:
                const video = new Video();
                video.fromJson(data);
                return video;

            case MediaType.AUDIO:
                throw new Error("Audio media type is not yet implemented");

            default:
                throw new Error(`Unsupported media type: ${type}`);
        }
    }

}