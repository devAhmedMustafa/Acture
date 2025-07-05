//
// Created by Ahmed Mustafa on 3/5/2025.
//

#ifndef STATION_TYPE_H
#define STATION_TYPE_H

namespace SPI {

    enum class STATION_TYPE : uint8_t {
        ROOT = 0,
        MCQ = 1,
        HISTORY = 2,
        LEAF = 255
    };

}

#endif //STATION_TYPE_H
