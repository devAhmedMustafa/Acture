//
// Created by Ahmed Mustafa on 5/2/2025.
//

#ifndef STATIONSERIALIZER_H
#define STATIONSERIALIZER_H

#include <fstream>
#include "../Stores/StationNetwork.h"

namespace SPI {
    class StationSerializer {

        void SerializeBase() const;
        void DeserializeBase(STATION_TYPE type, Application* context=nullptr);

    protected:
        StationPtr station;
        std::ostream& out;
        std::istream& in;

        virtual void SerializeBody() = 0;
        virtual void DeserializeBody() = 0;

    public:
        StationSerializer(std::ostream& out, std::istream& in);
        virtual ~StationSerializer() = default;

        void Serialize(const StationPtr& station);
        StationPtr& Deserialize(STATION_TYPE type);
    };
}

#endif //STATIONSERIALIZER_H
