//
// Created by Ahmed Mustafa on 4/20/2025.
//

#ifndef MEDIA_TYPE_H
#define MEDIA_TYPE_H

namespace SPI {

    enum class MEDIA_TYPE {
        NONE = -1,
        VIDEO = 0,
        AUDIO = 1,
        IMAGE = 2,
        TEXT = 3,
        PPTX = 4,
        UNKNOWN = 255
    };

}

#endif //MEDIA_TYPE_H
