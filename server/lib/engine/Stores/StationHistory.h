//
// Created by Ahmed Mustafa on 5/21/2025.
//

#ifndef STATIONHISTORY_H
#define STATIONHISTORY_H

#include <map>

#include "../Core/Core.h"

namespace SPI {
    class StationHistory {

        std::map<ID_T, int8_t> choicesTaken;

    public:
        std::map<ID_T, int8_t> GetChoicesTaken() const { return choicesTaken; }
        int8_t GetChoiceOfStation(ID_T id) const;
        void SetChoiceOfStation(ID_T id, thread_t choice);
        void RemoveChoiceOfStation(ID_T id);
        void ClearChoices();
    };
}

#endif //STATIONHISTORY_H
