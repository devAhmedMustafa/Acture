//
// Created by Ahmed Mustafa on 4/21/2025.
//

#ifndef ENGINESTATIONEDPAUSESTATE_H
#define ENGINESTATIONEDPAUSESTATE_H

#include "EngineStationedState.h"

namespace SPI {
    class EngineStationedPauseState final : public EngineStationedState {
    public:
        ~EngineStationedPauseState() override = default;

        void OnUpdate(Application& app, const float deltaTime) override {

        }
    };
}

#endif //ENGINESTATIONEDPAUSESTATE_H
