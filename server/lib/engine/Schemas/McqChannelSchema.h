//
// Created by Ahmed Mustafa on 4/30/2025.
//

#ifndef MCQCHANNELSCHEMA_H
#define MCQCHANNELSCHEMA_H

#include <string>
#include <vector>

#include "StationChannelSchema.h"

namespace SPI {
    struct McqChannelSchema final : StationChannelSchema {
        std::string question;
        std::vector<std::string> options;

        McqChannelSchema(const STATION_TYPE type, const bool pause, const float lifetime, std::string q, std::vector<std::string> opts)
            : StationChannelSchema(type, pause, lifetime), question(std::move(q)), options(std::move(opts)) {}
    };

    inline std::ostream& operator<<(std::ostream& os, const McqChannelSchema& schema) {
        os << "Does pause: " << schema.willPause << std::endl;
        os << "Question: " << schema.question << "\nOptions: ";
        for (const auto& option : schema.options) {
            os << option << " ";
        }
        return os;
    }
}

#endif //MCQCHANNELSCHEMA_H
