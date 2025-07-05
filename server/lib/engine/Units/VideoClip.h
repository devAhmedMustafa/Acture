//
// Created by Ahmed Mustafa on 6/30/2025.
//

#ifndef VIDEOCLIP_H
#define VIDEOCLIP_H

#include "Clip.h"

namespace SPI {

    class VideoClip : public Clip {

    public:
        itime_t start = 0;
        itime_t end = 0;

        VideoClip(const std::string& mediaPath, const itime_t start, const itime_t end) {
            mediaType = MEDIA_TYPE::VIDEO;
            this->start = start;
            this->end = end;
            this->mediaPath = mediaPath;
        }

    };

}

#endif //VIDEOCLIP_H
