//
// Created by Ahmed Mustafa on 5/2/2025.
//

#ifndef ENGINEREWINDSTATE_H
#define ENGINEREWINDSTATE_H

#include <iostream>

#include "EngineStateBase.h"

namespace SPI {
    class EngineRewindState final : public EngineStateBase {
    public:
        ~EngineRewindState() override = default;

        void OnEnter(Application& app) override {
            std::cout << "EngineState: Entering rewind state." << std::endl;

            app.GetStationManager()->ReverseTravel();
            app.GetTimeService()->SetLastTime(app.GetStationManager()->getPrevStation()->GetTimelapse());
            app.GetTimeService()->SetTime(app.GetStationManager()->getPrevStation()->GetTimelapse());
            app.GetTimeService()->ResetPlayingTime();

            const auto lastThread = app.GetStationManager()->getLastThread();
            const auto verse = app.GetStationManager()->getPrevStation()->GetConnectedVerse(lastThread);

            app.GetMediaBinder()->BindVerse(verse);

            app.TranslateState(EngineState::RUNNING);
        }

        void OnUpdate(Application& app, const float deltaTime) override {

        }
    };
}

#endif //ENGINEREWINDSTATE_H
