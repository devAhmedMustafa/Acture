//
// Created by Ahmed Mustafa on 7/1/2025.
//

#include "TimeTrigger.h"
#include "../Application.h"

namespace SPI {

    bool TimeTrigger::IsActive() const {
        if (context == nullptr) {
            return false; // Context is not set
        }

        const double currentTime = context->GetCurrentTime();
        const auto nextStation = context->GetStationManager()->getNextStation();

        if (nextStation == nullptr) {
            return false;
        }

        return currentTime == nextStation->GetTimelapse();

    }

} // namespace SPI