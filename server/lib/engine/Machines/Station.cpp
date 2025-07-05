//
// Created by am180 on 3/4/2025.
//

#include "Station.h"
#include <utility>
#include "../Utils/SMath.h"

namespace SPI {

    Station::~Station() {
        verses.clear();
        stations.clear();
    }

    void Station::ConnectStation(const thread_t thread, const std::shared_ptr<Station>& station) {
        if (thread >= this->stations.size()) {
            stations.resize(thread + 1);
        }
        if (thread >= this->verses.size()) {
            verses.resize(thread + 1);
        }

        stations[thread] = station->GetId();
        station->AddParent(shared_from_this());

        verses[thread] = new Verse();

        const ID_T verseId = SMath::EncodeBitPack(this->id, thread);
        verses[thread]->SetID(verseId);
    }

    void Station::DisconnectStation(const ID_T id) {

        auto it = std::find(stations.begin(), stations.end(), id);
        if (it != stations.end()) {
            const size_t index = std::distance(stations.begin(), it);
            stations.erase(it);
            delete verses[index];
            verses.erase(verses.begin() + index);
        }
    }

    void Station::PushStation(const std::shared_ptr<Station>& station) {
        ConnectStation(stations.size(), station);
    }

    void Station::AddParent(const StationPtr& parent) {
        if (parent == nullptr) return;
        parents.push_back(parent->GetId());
    }

}