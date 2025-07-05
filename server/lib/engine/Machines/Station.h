//
// Created by am180 on 3/4/2025.
//

#ifndef INTRASTATION_STATION_H
#define INTRASTATION_STATION_H

#include <functional>
#include <memory>
#include <vector>

#include "ITrigger.h"
#include "../Types/STATION_TYPE.h"
#include "../Units/Verse.h"
#include "../Core/Core.h"


namespace SPI {

    class Application;

    class Station : public std::enable_shared_from_this<Station> {

        using StationPtr = std::shared_ptr<Station>;

    protected:

        Application* context = nullptr;

        ID_T id = 0;

        STATION_TYPE type;
        itime_t timelapse = 0.0;
        lifetime_t lifetime = 0.0;

        std::vector<Verse*> verses;
        std::vector<ID_T> stations;
        std::vector<ID_T> parents;

        bool pause = true;

        std::function<void*()> onHookCallback;
        std::function<void*()> onUnhookCallback;

        ITrigger* trigger = nullptr;

    public:
        Station(const STATION_TYPE type) : type(type) {}

        Station(const STATION_TYPE type, Application * context) : context(context), type(type) {}

        virtual ~Station();

        virtual std::shared_ptr<Station> self() { return shared_from_this(); }

        void SetContext(Application* context) {
            this->context = context;
        }

        ID_T GetId() const { return id; }
        void SetId(const ID_T id) { this->id = id; }

        void SetTrigger(ITrigger* trigger) {
            this->trigger = trigger;
        }

        STATION_TYPE GetType() const { return type; }

        bool WillPause() const { return pause; }
        void SetPause(const bool pause) { this->pause = pause; }

        itime_t GetTimelapse() const { return timelapse; }
        void SetTimelapse(const itime_t timelapse) { this->timelapse = timelapse; }

        lifetime_t GetLifetime() const { return lifetime; }
        void SetLifetime(const lifetime_t lifetime) { this->lifetime = lifetime; }

        std::vector<ID_T> GetAllConnectedStations() const { return stations; }
        std::vector<Verse*> GetAllConnectedVerses() const { return verses; }

        ID_T GetConnectedStation(const thread_t thread) const {
            if (thread >= stations.size()) return 0;
            return stations[thread];
        }

        Verse* GetConnectedVerse(const thread_t idx) const {
            if (idx >= verses.size()) return nullptr;
            return verses[idx];
        }


        std::vector<ID_T> GetParents() const { return parents; }
        ID_T GetParent(const unsigned idx) const {
            if (idx >= parents.size()) return 0;
            return parents[idx];
        }
        void AddParent(const StationPtr& parent);

        void ConnectStation(thread_t thread, const std::shared_ptr<Station>& station);
        void DisconnectStation(ID_T id);
        void PushStation(const std::shared_ptr<Station>& station);

        void PushId(const ID_T id) { stations.push_back(id); }

        n_threads_t getThreadCount() const { return stations.size(); }

        virtual int AutoRoad() { return -1; }

        friend class StationNetwork;
        friend class StationManager;
    };

}

#endif //INTRASTATION_STATION_H
