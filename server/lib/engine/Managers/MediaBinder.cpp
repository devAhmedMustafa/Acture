#include "MediaBinder.h"

#include "TimeService.h"

namespace SPI {

    MediaBinder::MediaBinder() {
    }

    MediaBinder::~MediaBinder() {
    }

    void MediaBinder::BindVerse(Verse* verse) {
        this->verse = verse;
    }

    void MediaBinder::UnbindVerse() {
        this->verse = nullptr;
    }

    std::vector<std::shared_ptr<Clip>> MediaBinder::DataToBind(const double currentTime) {

        if (verse == nullptr) {
            std::cout << "No verse bound to MediaBinder" << std::endl;
            return {};
        }

        const auto tracks = verse->tracks;

        std::vector<std::shared_ptr<Clip>> clipsToBind(1);
        // currentClips.resize(1);

        clipsToBind.push_back(tracks[0]->clips[0]);

        return clipsToBind;

    }

}
