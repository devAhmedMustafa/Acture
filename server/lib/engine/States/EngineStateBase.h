//
// Created by am180 on 4/21/2025.
//

#ifndef INTRASTATIONENGINEWORKSPACE_ENGINESTATEBASE_H
#define INTRASTATIONENGINEWORKSPACE_ENGINESTATEBASE_H

namespace SPI {

    class Application;

    class EngineStateBase {
    public:
        virtual ~EngineStateBase() = default;

        virtual void OnEnter(Application&) = 0;
        virtual void OnUpdate(Application&, float) = 0;

    };

}

#endif //INTRASTATIONENGINEWORKSPACE_ENGINESTATEBASE_H
