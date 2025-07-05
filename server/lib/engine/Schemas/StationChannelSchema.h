//
// Created by Ahmed Mustafa on 4/30/2025.
//

#ifndef STATIONCHANNELSCHEMA_H
#define STATIONCHANNELSCHEMA_H

#include "../Types/STATION_TYPE.h"

namespace SPI {
    struct StationChannelSchema : std::enable_shared_from_this<StationChannelSchema> {
        STATION_TYPE stationType;
        bool willPause;
        float lifetime = 0.0f;

        StationChannelSchema(const STATION_TYPE type, const bool pause, const float lifetime = 0.0f)
            : stationType(type), willPause(pause), lifetime(lifetime) {}
        virtual ~StationChannelSchema() = default;
    };
}

#endif //STATIONCHANNELSCHEMA_H
