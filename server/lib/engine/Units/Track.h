//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_TRACK_H
#define INTRASTATION_TRACK_H

#include <iostream>
#include <map>
#include "Clip.h"
#include "../Types/MEDIA_TYPE.h"
#include "../Core/Core.h"

namespace SPI {

    class Track {

        MEDIA_TYPE mediaType = MEDIA_TYPE::NONE;
        itime_t length;

        itime_t CalculateLength();

    public:

        Track();
        ~Track();

        void AddClip(itime_t position, const std::shared_ptr<Clip>& clip);
        void RemoveClip(itime_t position);
        void ClearClips();

        std::shared_ptr<Clip> GetClip(itime_t position) const;

        itime_t GetLength() const {
            return length;
        }

        MEDIA_TYPE GetMediaType() const {
            return mediaType;
        }
        
        void SetMediaType(const MEDIA_TYPE type) {
            mediaType = type;
        }

        size_t GetClipCount() const {
            return clips.size();
        }


        std::map<itime_t, std::shared_ptr<Clip>> clips;
    };

}

#endif //INTRASTATION_TRACK_H
