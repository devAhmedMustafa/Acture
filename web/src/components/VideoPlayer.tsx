import YoutubeEmbed from "../utils/YoutubeEmbed";

export default function VideoPlayer({ mediaPath }: { mediaPath: string }) {

    // Analyze media path source
    const isYoutube = mediaPath.includes("youtube.com") || mediaPath.includes("youtu.be");

    if (isYoutube) {
        const videoId = new URL(mediaPath).searchParams.get("v") || mediaPath.split("/").pop();
        return <YoutubeEmbed videoId={videoId || ""} />;
    }

}