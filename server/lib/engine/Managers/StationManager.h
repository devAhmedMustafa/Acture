//
// Created by Ahmed Mustafa on 3/5/2025.
//

#ifndef STATIONMANAGER_H
#define STATIONMANAGER_H
#include "../Machines/Station.h"
#include "../Core/RootStation.h"
#include <stack>

#include "../Stores/StationNetwork.h"
#include "../Stores/StationHistory.h"

namespace SPI {

    class StationManager {

        std::shared_ptr<RootStation> rootStation = std::make_shared<RootStation>();
        StationPtr prevStation;
        StationPtr nextStation;

        std::stack<StationPtr> history;
        std::stack<unsigned int> threadHistory;

        bool stationed = false;

        StationNetwork* network;
        StationHistory* stationHistory;

        float callingThreshold = 0.01f;


    
    public:
        StationManager();
        ~StationManager();
        
        StationPtr getPrevStation() { return prevStation; }
        StationPtr getNextStation() { return nextStation; }
        StationNetwork* getNetwork() const { return network; }
        StationHistory* getStationHistory() const { return stationHistory; }
        unsigned int getLastThread() { return threadHistory.top(); }
        
        void InitializeStation();
        
        void Travel(unsigned int thread);
        void ReverseTravel();
        void CalculateNextTimelapse();

        bool CheckNextTrigger() const;

        friend class StationNetworkSerializer;
    };

}




#endif //STATIONMANAGER_H
