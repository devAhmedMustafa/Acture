//
// Created by Ahmed Mustafa on 3/5/2025.
//

#ifndef LEAFSTATION_H
#define LEAFSTATION_H

#include "../Machines/Station.h"

using str = std::string;

namespace SPI {

    class LeafStation final : public Station {

    public:
        explicit LeafStation() : Station(STATION_TYPE::LEAF) {}

        std::shared_ptr<Station> self() override { 
            return std::static_pointer_cast<Station>(shared_from_this()); 
        }
    };

}

#endif
