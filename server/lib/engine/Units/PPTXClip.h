//
// Created by Ahmed Mustafa on 6/30/2025.
//

#ifndef PPTXCLIP_H
#define PPTXCLIP_H

#include "Clip.h"

namespace SPI {

    class PPTXClip : public Clip {
    public:
        PPTXClip() {
            mediaType = MEDIA_TYPE::PPTX;
        }
    };

}

#endif //PPTXCLIP_H
