//
// Created by Ahmed Mustafa on 4/25/2025.
//

#ifndef STATIONTYPEMAPPER_H
#define STATIONTYPEMAPPER_H
#include "../Features/MCQStation.h"

#include "../Core/LeafStation.h"
#include "../Machines/Station.h"
#include "../Features/History/HistoryStation.h"

namespace SPI {
    inline std::shared_ptr<Station> CreateStation(const STATION_TYPE type, Application* context) {
        switch (type) {
            case STATION_TYPE::ROOT:
                return std::make_shared<RootStation>(RootStation());
            case STATION_TYPE::MCQ:
                return std::make_shared<MCQStation>(MCQStation());
            case STATION_TYPE::HISTORY:
                return std::make_shared<HistoryStation>(HistoryStation(context));
            case STATION_TYPE::LEAF:
                return std::make_shared<LeafStation>(LeafStation());
            default:
                return nullptr;
        }
    }

}

#endif //STATIONTYPEMAPPER_H
