import { useEffect, useState } from "react";
import { useSocketContext } from "../contexts/SocketContext";
import { Media } from "../types/Media";
import MediaMapper from "../mappers/MediaMapper";

export default function MediaEngigne(){

    const {messages} = useSocketContext();
    const [currentMedia, setCurrentMedia] = useState<Media|null>(null);

    useEffect(()=> {
        const mediaMessages = messages.filter(m => m.type === "media");
        if (mediaMessages.length === 0) return;

        const currentMedia = mediaMessages[mediaMessages.length - 1].payload;
        const media = MediaMapper.getFromType(currentMedia, currentMedia.media_type); 

        console.log("Current media:", currentMedia);

        media.fromJson(currentMedia);
        setCurrentMedia(media);

    }, [messages]);


    return {currentMedia}
}