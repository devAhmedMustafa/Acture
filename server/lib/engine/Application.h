#pragma once

#include "Channels/StationChannel.h"
#include "Core/EngineState.h"
#include "Events/StationCallEvent.h"
#include "Managers/TimeService.h"
#include "Managers/StationManager.h"
#include "Managers/MediaBinder.h"
#include "States/EngineStateBase.h"

namespace SPI
{
    class Application
    {
        std::unique_ptr<EngineStateBase> appState;
        EngineState stateType;

        TimeService* timeService;
        StationManager* stationManager;
        MediaBinder* mediaBinder;

        unsigned int currentThread = 0;

        // Events
        StationCallEvent stationCallEvent;

        // Pipeline
        StationChannel stationChannel;

    public:

        Application();
        ~Application();

        void TranslateState(EngineState newState);

        unsigned int GetCurrentThread() const { return currentThread; }
        void SetCurrentThread(const unsigned int thread) { currentThread = thread; }

        EngineState GetCurrentState() const { return stateType; }

        double GetCurrentTime() const
        {
            return timeService->GetMainTime();
        }

        StationNetwork* GetStationNetwork()
        {
            return stationManager->getNetwork();
        }

        MediaBinder* GetMediaBinder() const {
            return mediaBinder;
        }

        TimeService* GetTimeService() const {
            return timeService;
        }

        StationManager* GetStationManager() const {
            return stationManager;
        }

        StationCallEvent* GetStationCallEvent()
        {
            return &stationCallEvent;
        }

        StationChannel* GetStationChannel()
        {
            return &stationChannel;
        }

        void OnUpdate(float deltaTime);
        std::vector<std::shared_ptr<Clip>> DataToBind() const;

        void Play();
        void Pause();
        void Travel(unsigned int thread);
        void Rewind();
        void Serialize();
        void Deserialize();
        void ScrubTime(float time) const;

        friend class Editor;
    };

}
