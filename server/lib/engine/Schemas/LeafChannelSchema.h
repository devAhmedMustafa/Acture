//
// Created by Ahmed Mustafa on 5/1/2025.
//

#ifndef LEAFCHANNELSCHEMA_H
#define LEAFCHANNELSCHEMA_H
#include "StationChannelSchema.h"

namespace SPI {

    struct LeafChannelSchema final : StationChannelSchema {
        LeafChannelSchema() : StationChannelSchema(STATION_TYPE::LEAF, true) {}
    };

}

#endif //LEAFCHANNELSCHEMA_H
