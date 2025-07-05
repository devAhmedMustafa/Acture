//
// Created by Ahmed Mustafa on 4/30/2025.
//

#ifndef SCHEMAGENERATOR_H
#define SCHEMAGENERATOR_H
#include "../Features/MCQStation.h"

#include "../Schemas/StationChannelSchema.h"
#include "../Machines/Station.h"
#include "../Schemas/McqChannelSchema.h"
#include "../Schemas/LeafChannelSchema.h"

namespace SPI {
    inline std::shared_ptr<StationChannelSchema> GenerateStationChannel(const std::shared_ptr<Station>& station) {
        switch (station->GetType()) {

            case STATION_TYPE::MCQ: {
                const auto mcqStation = std::dynamic_pointer_cast<MCQStation>(station);

                return std::make_shared<McqChannelSchema>(
                    McqChannelSchema{
                        mcqStation->GetType(),
                        mcqStation->WillPause(),
                        mcqStation->GetLifetime(),
                        mcqStation->getQuestion(),
                        mcqStation->getOptions()
                    }
                );
            }

            case STATION_TYPE::LEAF: {
                return std::make_shared<LeafChannelSchema>(LeafChannelSchema{});
            }

            default:
                throw std::runtime_error("Unknown station type");
        }
    }

}

#endif //SCHEMAGENERATOR_H
