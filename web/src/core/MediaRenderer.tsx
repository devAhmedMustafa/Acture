import VideoPlayer from "../components/VideoPlayer";
import MediaEngigne from "./MediaEngine";

export default function MediaRenderer() {
    
    const { currentMedia } = MediaEngigne();
    if (!currentMedia) {
        return (
            <div>
                <p>No media is currently available.</p>
            </div>
        );
    }

    switch (currentMedia.mediaType) {
        case 0: // VIDEO
            return (
                <VideoPlayer mediaPath={currentMedia.mediaPath} />
            )

        default: // Unsupported media type
            console.warn(`Unsupported media type: ${currentMedia.mediaType}`);
            return (
                <div>
                    <p>Unsupported media type: {currentMedia.mediaType}</p>
                </div>
            )

    }

}