//
// Created by Ahmed Mustafa on 5/3/2025.
//

#ifndef VERSESERIALIZER_H
#define VERSESERIALIZER_H

#include "../Units/Verse.h"
#include "../Types/ASSETS_MODE.h"

namespace SPI {
    class AssetSerializer {

        std::ostream& out;
        ASSETS_MODE mode;

    public:
        explicit AssetSerializer(std::ostream& out, const ASSETS_MODE mode=ASSETS_MODE::BUNDLE) : out(out), mode(mode) {}
        ~AssetSerializer() = default;

        void Serialize(const Clip*) const;
    };
}

#endif //VERSESERIALIZER_H
