//
// Created by am180 on 3/6/2025.
//

#include "Verse.h"

namespace SPI {

    Verse::Verse()
    = default;

    Verse::~Verse() {
        for (const auto* track : tracks) {
            delete track;
        }
    }

    void Verse::CreateTrack()
    {
        auto* newTrack = new Track();
        tracks.emplace_back(newTrack);
    }

    void Verse::DeleteTrack(const thread_t idx){

        if (idx >= tracks.size()) return;
        delete tracks[idx];
        tracks.erase(tracks.begin() + idx);
    }

    itime_t Verse::CalculateLength()
    {
        itime_t length = 0;
        for (const auto* track : tracks) {
            if (track->GetLength() > length) {
                length = track->GetLength();
            }
        }

        this->length = length;

        return length;
    }
}