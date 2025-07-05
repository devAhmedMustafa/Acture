//
// Created by Ahmed Mustafa on 3/5/2025.
//

#include "StationManager.h"

namespace SPI {


    StationManager::StationManager() : network(new StationNetwork(rootStation)), stationHistory(new StationHistory()) {
        nextStation = nullptr;
        this->InitializeStation();
        rootStation.reset();
    }

    StationManager::~StationManager() {
        delete network;
        rootStation.reset();
        prevStation.reset();
        nextStation.reset();
    }

    void StationManager::InitializeStation(){
        prevStation = rootStation;
        nextStation = rootStation;
    }

    void StationManager::CalculateNextTimelapse() {
        if (nextStation == nullptr) return;
        const auto willPause = nextStation->WillPause();

        const auto currentVerse = prevStation->GetConnectedVerse(threadHistory.top());
        if (currentVerse == nullptr) {
            std::cerr << "Current verse is null." << std::endl;
            return;
        }

        currentVerse->CalculateLength();

        const auto newTimelapse = prevStation->GetTimelapse() + currentVerse->GetLength() + nextStation->GetLifetime() * (willPause ? 0.0f : -1.0f);

        nextStation->SetTimelapse(newTimelapse);
    }

    void StationManager::Travel(const unsigned int thread)
    {
        if (nextStation == nullptr) return;
        history.push(prevStation);
        prevStation = nextStation;
        nextStation = network->GetStationById(nextStation->GetConnectedStation(thread));
        threadHistory.push(thread);

        // CalculateNextTimelapse();

        stationHistory->SetChoiceOfStation(prevStation->GetId(), thread);

        stationed = false;
    }

    void StationManager::ReverseTravel()
    {
        if (history.size() <= 1) return;
        nextStation = prevStation;
        prevStation = history.top();
        history.pop();
        threadHistory.pop();
    }

    bool StationManager::CheckNextTrigger() const {
        if (nextStation == nullptr) return false;
        if (nextStation->trigger == nullptr) return false;

        return nextStation->trigger->IsActive() && !stationed;
    }

    
}
