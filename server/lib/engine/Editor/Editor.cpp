//
// Created by Ahmed Mustafa on 4/25/2025.
//

#include "Editor.h"

#include <iostream>
#include <utility>

#include "../Utils/SMath.h"
#include "../Mappers/StationTypeMapper.h"
#include "../Units/VideoClip.h"

namespace SPI {
    Editor::Editor(Application& app) : app(app) {
        // Constructor implementation
    }

    ID_T Editor::AddStation(const ID_T id, const STATION_TYPE type, const itime_t timelapse) const {

        const auto createdId = SMath::GenerateId();

        const auto createdStation = CreateStation(type, &app);
        if (createdStation == nullptr) {
            std::cerr << "Failed to create station of type: " << static_cast<int>(type) << std::endl;
            return 0;
        }
        createdStation->SetId(createdId);
        createdStation->SetTimelapse(timelapse);
        this->AddStationInstance(id, createdStation);

        return createdId;
    }

    ID_T Editor::AddStationToNetwork(STATION_TYPE type) const
    {
        const auto createdId = SMath::GenerateId();

        const auto createdStation = CreateStation(type, &app);
        if (createdStation == nullptr) {
            std::cerr << "Failed to create station of type: " << static_cast<int>(type) << std::endl;
            return 0;
        }
        createdStation->SetId(createdId);
        app.stationManager->getNetwork()->AddStation(createdStation);

        return createdId;
    }

    void Editor::InitializeVerse(Verse* verse, const std::string& mediaPath, const float duration) const {
        verse->CreateTrack();
        VideoClip clip {mediaPath, 0, duration};

        verse->tracks[0]->AddClip(0, std::make_shared<VideoClip>(clip));
    }

    void Editor::AddStationInstance(const ID_T parentId, const std::shared_ptr<Station>& station) const {
        const auto csId = app.stationManager->getNetwork()->PushStation(parentId, station);
        SMath::ReserveId(csId);

        if (app.GetCurrentState() == EngineState::EMPTY){
            app.Travel(0);
            app.TranslateState(EngineState::PAUSED);
        }
    }

    Clip* Editor::CreateClip(std::string mediaPath, const itime_t start, const itime_t end) {
        const auto clip = new VideoClip{mediaPath, start, end};
        return clip;
    }

    void Editor::RemoveStation(const ID_T id) const {
        app.stationManager->getNetwork()->RemoveStation(id);
    }
}
