//
// Created by Ahmed Mustafa on 4/25/2025.
//

#ifndef EXTENTIONMEDIATYPEMAPPER_H
#define EXTENTIONMEDIATYPEMAPPER_H
#include <string>
#include "../Types/MEDIA_TYPE.h"

namespace SPI {
    inline MEDIA_TYPE GetMediaTypeFromExtension(const std::string& extension) {
        if (extension == ".mp4" || extension == ".avi") {
            return MEDIA_TYPE::VIDEO;
        }
        if (extension == ".mp3" || extension == ".wav") {
            return MEDIA_TYPE::AUDIO;
        }
        if (extension == ".jpg" || extension == ".png") {
            return MEDIA_TYPE::IMAGE;
        }
        if (extension == ".txt") {
            return MEDIA_TYPE::TEXT;
        }
        
        return MEDIA_TYPE::NONE;
    }
}

#endif //EXTENTIONMEDIATYPEMAPPER_H
