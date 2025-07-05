//
// Created by am180 on 3/6/2025.
//

#ifndef INTRASTATION_STATIONSTORE_H
#define INTRASTATION_STATIONSTORE_H

#include "../Core/Core.h"
#include "../Machines/Station.h"
#include "../Core/RootStation.h"

namespace SPI {

    using StationPtr = std::shared_ptr<Station>;

    class StationNetwork {

        std::shared_ptr<RootStation> root;
        std::map<ID_T, StationPtr> stations;
        stations_size_t count = 0;

        ID_T SearchForId(const StationPtr& station);

    public:
        StationNetwork();
        explicit StationNetwork(std::shared_ptr<RootStation> rootStation);
        ~StationNetwork();

        StationPtr GetRoot() { return root; }
        stations_size_t Size() const { return count; }

        std::vector<ID_T> GetAllStationIds() const;
        std::vector<StationPtr> GetAllStations() const;

        StationPtr GetStationById(ID_T id);
        Verse* GetVerseById(ID_T id);

        void AddStation(const StationPtr& station);
        ID_T PushStation(ID_T subRootId, const StationPtr& stationToPush);
        void RemoveStation(ID_T id);

        friend class StationNetworkSerializer;

    };
}

#endif //INTRASTATION_STATIONSTORE_H
