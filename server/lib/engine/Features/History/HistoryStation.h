//
// Created by Ahmed Mustafa on 5/21/2025.
//

#ifndef HISTORYSTATION_H
#define HISTORYSTATION_H

#include "../../Machines/Station.h"

class Application;

namespace SPI {

    class HistoryStation final : public Station {

        std::vector<ID_T> stationsIds;
        std::map<std::string, thread_t> gates;

    public:
        HistoryStation() : Station(STATION_TYPE::HISTORY) {}
        HistoryStation(Application* context) : Station(STATION_TYPE::HISTORY, context) {}

        std::shared_ptr<Station> self() override {
            return std::static_pointer_cast<Station>(shared_from_this());
        }

        void UseStation(ID_T id);
        std::vector<ID_T> GetStationsIds() const { return stationsIds; }
        void RemoveStation(ID_T id);
        void RemoveStationByIndex(size_t index);

        void CreateNewGate();
        void SetGate(const std::string &gateId, const std::string& gateValue);
        thread_t GetGate(std::string gateId) const { return gates.find(gateId)->second; }
        std::map<std::string, thread_t> GetGates() const { return gates; }
        bool IsGateExist(const std::string& gateId) const { return gates.find(gateId) != gates.end(); }

        int AutoRoad() override;

    };

}

#endif //HISTORYSTATION_H
