import { Icon } from "@iconify/react/dist/iconify.js";

export default function YoutubeEmbed({ videoId }: { videoId: string }) {
    return (
        <div className="w-full h-full flex flex-col gap-2">

            <div className="flex items-center gap-2">
                <Icon icon="logos:youtube-icon" className="text-lg inline" />
                <h2 className="text-lg font-semibold inline !text-text-muted">YouTube Video</h2>
            </div>


            <iframe
                className="w-full h-full rounded-lg"
                src={`https://www.youtube.com/embed/${videoId}`}
                title="YouTube video player"
                allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture"
                allowFullScreen
            ></iframe>
        </div>
    );
}