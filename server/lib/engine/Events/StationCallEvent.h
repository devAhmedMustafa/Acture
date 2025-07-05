//
// Created by Ahmed Mustafa on 4/30/2025.
//

#ifndef STATIONCALLEVENT_H
#define STATIONCALLEVENT_H
#include "../Events/Event.h"
#include "../Schemas/StationChannelSchema.h"

namespace SPI {

    class StationCallEvent : public Event<StationChannelSchema> {};

}

#endif //STATIONCALLEVENT_H
