//
// Created by Ahmed Mustafa on 4/21/2025.
//

#ifndef ENGINETRAVELLINGSTATE_H
#define ENGINETRAVELLINGSTATE_H

#include "EngineStateBase.h"
#include "../Managers/StationManager.h"

namespace SPI {
    class EngineTravellingState final : public EngineStateBase {
    public:
        ~EngineTravellingState() override = default;

        void OnEnter(Application& app) override {
            app.GetStationManager()->Travel(app.GetCurrentThread());
            const auto verse = app.GetStationManager()->getPrevStation()->GetConnectedVerse(app.GetCurrentThread());
            app.GetMediaBinder()->BindVerse(verse);

            app.GetTimeService()->ResetPlayingTime();
            app.GetTimeService()->SetLastTime(app.GetStationManager()->getPrevStation()->GetTimelapse());

            app.TranslateState(EngineState::RUNNING);
            app.SetCurrentThread(-1);
        }

        void OnUpdate(Application& app, const float deltaTime) override {

        }
    };
}

#endif //ENGINETRAVELLINGSTATE_H
