//
// Created by Ahmed Mustafa on 3/5/2025.
//

#ifndef ROOTSTATION_H
#define ROOTSTATION_H

#include "../Machines/Station.h"

using str = std::string;

namespace SPI {

    class RootStation final : public Station {


    public:
        explicit RootStation() : Station(STATION_TYPE::ROOT) {
            pause = false;
        }
    };

}

#endif
