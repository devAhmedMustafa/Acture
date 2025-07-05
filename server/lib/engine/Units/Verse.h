//
// Created by am180 on 3/6/2025.
//

#ifndef INTRASTATION_VERSE_H
#define INTRASTATION_VERSE_H

#include "Track.h"
#include <vector>
#include "../Core/Core.h"

namespace SPI {

    class Verse {

        ID_T id;
        itime_t length{};

    public:

        std::vector<Track*> tracks;

        Verse();
        ~Verse();

        ID_T GetID() const {
            return id;
        }
        void SetID(const ID_T newID) {
            id = newID;
        }

        void CreateTrack();
        void DeleteTrack(thread_t idx);
        itime_t CalculateLength();

        itime_t GetLength() const {return length;}

    };

}

#endif //INTRASTATION_VERSE_H
