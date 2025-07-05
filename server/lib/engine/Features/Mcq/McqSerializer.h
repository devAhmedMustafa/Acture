//
// Created by Ahmed Mustafa on 5/2/2025.
//

#ifndef MCQSERIALIZER_H
#define MCQSERIALIZER_H
#include "../../Serializers/StationSerializer.h"

namespace SPI {

    class McqSerializer final : public StationSerializer {
    public:
        explicit McqSerializer(std::ostream& out, std::istream& in);
        ~McqSerializer() override = default;
    protected:
        void SerializeBody() override;
        void DeserializeBody() override;
    };

}




#endif //MCQSERIALIZER_H
