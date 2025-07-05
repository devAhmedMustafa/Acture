//
// Created by Ahmed Mustafa on 5/2/2025.
//

#ifndef NOBODYSERIALIZER_H
#define NOBODYSERIALIZER_H
#include "StationSerializer.h"

namespace SPI {

    class NoBodySerializer final : public StationSerializer{
    public:
        explicit NoBodySerializer(std::ostream &out, std::istream &in) : StationSerializer(out, in) {}

        void SerializeBody() override {
        }
        void DeserializeBody() override {
        }
    };

} // namespace SPI

#endif //NOBODYSERIALIZER_H
