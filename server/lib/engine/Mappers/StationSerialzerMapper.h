//
// Created by Ahmed Mustafa on 5/2/2025.
//

#ifndef STATIONSERIALZERMAPPER_H
#define STATIONSERIALZERMAPPER_H
#include "../Serializers/StationSerializer.h"
#include "../Types/STATION_TYPE.h"
#include "../Features/Mcq/McqSerializer.h"
#include "../Serializers/NoBodySerializer.h"

namespace SPI {
    inline StationSerializer* CreateStationSerializer(const STATION_TYPE type, std::ostream &out, std::istream &in, Application* context) {
        switch (type) {
            case STATION_TYPE::ROOT:
                return new NoBodySerializer(out, in);
            case STATION_TYPE::LEAF:
                return new NoBodySerializer(out, in);
            case STATION_TYPE::MCQ:
                return new McqSerializer(out, in);
            default:
                return new NoBodySerializer(out, in);
        }

    }
}

#endif //STATIONSERIALZERMAPPER_H
