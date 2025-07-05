//
// Created by am180 on 4/21/2025.
//

#ifndef INTRASTATIONENGINEWORKSPACE_ENGINEPAUSEDSTATE_H
#define INTRASTATIONENGINEWORKSPACE_ENGINEPAUSEDSTATE_H

#include "EngineStateBase.h"

namespace SPI {
    class EnginePausedState final : public EngineStateBase {
    public:
        ~EnginePausedState() override = default;

        void OnEnter(Application& app) override {
        }

        void OnUpdate(Application& app, float deltaTime) override {
            // Paused state does not perform any updates
        }
    };
}

#endif //INTRASTATIONENGINEWORKSPACE_ENGINEPAUSEDSTATE_H
