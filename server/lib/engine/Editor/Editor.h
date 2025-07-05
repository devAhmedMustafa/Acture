//
// Created by Ahmed Mustafa on 4/25/2025.
//

#ifndef EDITOR_H
#define EDITOR_H
#include "../Application.h"
#include "../Core/Core.h"


namespace SPI {
    class Editor {

        Application& app;

    public:
        Editor(Application& app);
        ~Editor() {}

        ID_T AddStation(ID_T id, STATION_TYPE type, itime_t timelapse) const;
        ID_T AddStationToNetwork(STATION_TYPE type) const;
        void InitializeVerse(Verse* verse, const std::string& mediaPath, float duration) const;

        void AddStationInstance(ID_T parentId, const std::shared_ptr<Station>& station) const;

        Clip* CreateClip(std::string mediaPath, itime_t start, itime_t end);

        void RemoveStation(ID_T id) const;

    };
}

#endif //EDITOR_H
