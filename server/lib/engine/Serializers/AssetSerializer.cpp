//
// Created by Ahmed Mustafa on 5/3/2025.
//

#include "AssetSerializer.h"

#include "Utils/AssetBundle.h"

namespace SPI {

    void AssetSerializer::Serialize(const Clip* clip) const {
        const auto path = clip->mediaPath;

        switch (mode) {

            case ASSETS_MODE::BUNDLE: {
                AssetBundle::CreateBundle(out, path);
                break;
            }

            case ASSETS_MODE::INFILE_REF: {
                const uint32_t pathLength = path.size();
                out.write(reinterpret_cast<const char*>(&pathLength), sizeof(pathLength));
                out.write(path.c_str(), pathLength);
                break;
            }

            case ASSETS_MODE::EXTERNAL_REF: {
                if (!clip->externalRef.empty()) {
                    const uint32_t externalRefLength = clip->externalRef.size();
                    out.write(reinterpret_cast<const char*>(&externalRefLength), sizeof(externalRefLength));
                    out.write(clip->externalRef.c_str(), externalRefLength);
                } else {
                    constexpr uint32_t externalRefLength = 0;
                    out.write(reinterpret_cast<const char*>(&externalRefLength), sizeof(externalRefLength));
                }
                break;
            }

        }

    }

}
