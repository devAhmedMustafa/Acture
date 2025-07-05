//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_CLIP_H
#define INTRASTATION_CLIP_H

#include <string>
#include "../Types/MEDIA_TYPE.h"

namespace SPI {

    class Clip {
    public:

        virtual ~Clip()= default;

        MEDIA_TYPE mediaType = MEDIA_TYPE::UNKNOWN;
        std::string mediaPath;

        std::string externalRef;

        bool operator!() const;
    };

}


#endif //INTRASTATION_CLIP_H
