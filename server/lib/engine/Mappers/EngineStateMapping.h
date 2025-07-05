//
// Created by Ahmed Mustafa on 4/21/2025.
//

#ifndef ENGINESTATEMAPPING_H
#define ENGINESTATEMAPPING_H

#include <memory>
#include "../Core/EngineState.h"

#include "../States/EngineStateBase.h"

#include "../States/EngineEmptyState.h"
#include "../States/EngineRunningState.h"
#include "../States/EnginePausedState.h"
#include "../States/EngineStationedPauseState.h"
#include "../States/EngineStationedRunState.h"
#include "../States/EngineTravellingState.h"
#include "../States/EngineRewindState.h"

namespace SPI {
    inline std::unique_ptr<EngineStateBase> CreateEngineState(const EngineState state) {
        switch (state) {
            case EngineState::RUNNING:
                return std::make_unique<EngineRunningState>();
            case EngineState::PAUSED:
                return std::make_unique<EnginePausedState>();
            case EngineState::STATIONED_RUN:
                return std::make_unique<EngineStationedRunState>();
            case EngineState::STATIONED_PAUSE:
                return std::make_unique<EngineStationedPauseState>();
            case EngineState::FORWARDING:
                return std::make_unique<EngineTravellingState>();
            case EngineState::REWINDING:
                return std::make_unique<EngineRewindState>();
            default:
                return std::make_unique<EngineEmptyState>();
        }
    }

}

#endif //ENGINESTATEMAPPING_H
