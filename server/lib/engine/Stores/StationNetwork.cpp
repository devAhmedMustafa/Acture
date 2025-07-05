//
// Created by Ahmed Mustafa on 4/20/2025.
//

#include "StationNetwork.h"

#include <iostream>
#include <utility>

#include "../Utils/SMath.h"


namespace SPI {

    StationNetwork::StationNetwork() = default;

    StationNetwork::StationNetwork(std::shared_ptr<RootStation> rootStation) : count(1) {
        root = std::move(rootStation);
        stations.insert({0, root});
    }

    StationNetwork::~StationNetwork() {
        root.reset();
        stations.clear();
    }

    std::vector<ID_T> StationNetwork::GetAllStationIds() const
    {
        std::vector<ID_T> ids;

        ids.reserve(stations.size());
        for (const auto& [key, value] : stations) {
            ids.push_back(key);
        }
        return ids;
    }

    std::vector<StationPtr> StationNetwork::GetAllStations() const
    {
        std::vector<StationPtr> allStations;

        allStations.reserve(stations.size());
        for (const auto& [key, value] : stations) {
            allStations.push_back(value);
        }
        return allStations;
    }

    StationPtr StationNetwork::GetStationById(const ID_T id)
    {

        if (id < 0) {
            std::cerr << "Invalid station ID: " << id << std::endl;
            throw std::invalid_argument("Cannot get the root station");
        }

        const auto stationFound = stations.find(id);
        if (stationFound == stations.end()) {
            std::cerr << "Station with ID " << id << " not found." << std::endl;
            return nullptr;
        }

        return stationFound->second;
    }

    void StationNetwork::AddStation(const StationPtr &station)
    {
        if (station == nullptr) {
            std::cerr << "Cannot add a null station" << std::endl;
            throw std::invalid_argument("Cannot add a null station");
        }

        const auto id = SearchForId(station);
        if (id != 0) {
            std::cerr << "Station with ID " << id << " already exists." << std::endl;
            return;
        }

        stations.insert({station->GetId(), station});
        count++;
    }

    ID_T StationNetwork::PushStation(const ID_T subRootId, const StationPtr &stationToPush)
    {
        const auto subRootStation = GetStationById(subRootId);

        if (!subRootStation) {
            throw std::invalid_argument("Cannot push to a non-existing station");
        }

        subRootStation->PushStation(stationToPush);
        stations.insert({stationToPush->GetId(), stationToPush});

        count++;

        return stationToPush->GetId();
    }

    void StationNetwork::RemoveStation(const ID_T id) {

        if (id <= 0) {
            throw std::invalid_argument("Cannot remove the root station");
        }

        auto stationToRemove = GetStationById(id);
        if (!stationToRemove) return;

        for (const auto& parentId : stationToRemove->parents) {
            auto parentStation = GetStationById(parentId);
            if (parentStation) {
                parentStation->DisconnectStation(id);
            }
        }

        stationToRemove.reset();
        stations.erase(id);
        count--;
    }

    ID_T StationNetwork::SearchForId(const StationPtr& station) {
        for (const auto& [key, value] : stations) {
            if (value == station) {
                return key;
            }
        }
        return 0;
    }

    Verse* StationNetwork::GetVerseById(const ID_T id) {

        const auto ids = SMath::Decode2BitPack(id);
        const auto parentId = ids[0];
        const auto thread = ids[1];

        const auto station = GetStationById(parentId);
        if (!station) {
            std::cerr << "Station with ID " << id << " not found." << std::endl;
            return nullptr;
        }

        return station->GetConnectedVerse(thread);
    }

}
