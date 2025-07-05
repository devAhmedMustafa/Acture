//
// Created by Ahmed Mustafa on 4/20/2025.
//

#include "Clip.h"

namespace SPI {

    bool Clip::operator!() const {
        return mediaPath.empty();
    }

}