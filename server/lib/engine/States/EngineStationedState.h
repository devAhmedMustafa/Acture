//
// Created by Ahmed Mustafa on 4/30/2025.
//

#ifndef ENGINESTATIONEDSTATE_H
#define ENGINESTATIONEDSTATE_H

#include "EngineStateBase.h"
#include "../Mappers/SchemaGenerator.h"

namespace SPI {

    class EngineStationedState : public EngineStateBase {
    public:
        ~EngineStationedState() override = default;

        void OnEnter(Application& app) override {
            std::cout << "EngineState: Entering station state." << std::endl;

            const auto& station = app.GetStationManager()->getNextStation();
            const auto autoThread = station->AutoRoad();

            if (autoThread == -1) {
                const auto channelData = GenerateStationChannel(station);
                app.GetStationCallEvent()->Dispatch(channelData);
            }
            else {
                app.Travel(autoThread);
            }
        }

    };
}

#endif //ENGINESTATIONEDSTATE_H
