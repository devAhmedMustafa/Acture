//
// Created by am180 on 4/21/2025.
//

#ifndef INTRASTATIONENGINEWORKSPACE_ENGINEEMPTYSTATE_H
#define INTRASTATIONENGINEWORKSPACE_ENGINEEMPTYSTATE_H

#include <iostream>

#include "EngineStateBase.h"

namespace SPI {
    class EngineEmptyState : public EngineStateBase {
    public:
        virtual ~EngineEmptyState() = default;

        void OnEnter(Application& app) override {
            std::cout << "EngineState: Entering empty state." << std::endl;
        }

        void OnUpdate(Application& app, float deltaTime) override {
            // Empty state does not perform any updates
        }
    };
}

#endif //INTRASTATIONENGINEWORKSPACE_ENGINEEMPTYSTATE_H
