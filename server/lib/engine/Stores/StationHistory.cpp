//
// Created by Ahmed Mustafa on 5/21/2025.
//

#include "StationHistory.h"

namespace SPI {

    int8_t StationHistory::GetChoiceOfStation(const ID_T id) const {
        auto it = choicesTaken.find(id);
        if (it != choicesTaken.end()) {
            return it->second;
        }
        return -1;
    }

    void StationHistory::SetChoiceOfStation(const ID_T id, const thread_t choice) {
        auto it = choicesTaken.find(id);
        if (it == choicesTaken.end())
            choicesTaken.insert({id, choice});
        else
            choicesTaken[id] = choice;
    }

    void StationHistory::RemoveChoiceOfStation(const ID_T id) {
        choicesTaken.erase(id);
    }

    void StationHistory::ClearChoices() {
        choicesTaken.clear();
    }

}