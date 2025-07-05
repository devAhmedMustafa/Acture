//
// Created by am180 on 3/6/2025.
//

#include "TimeService.h"

#include <stdexcept>

namespace SPI {

    TimeService* TimeService::instance = nullptr;

    TimeService::TimeService() {
        if (instance) throw std::runtime_error("TimeService instance already exists");
        instance = this;
    }

    TimeService::~TimeService() {
        if (instance == this) instance = nullptr;
    }

    void TimeService::SetTime(const double newTime) {
        if (newTime < 0) throw std::invalid_argument("Time cannot be negative");
        mainTimer = newTime;
        playerTimer = newTime - lastTime;
    }

    void TimeService::ResetPlayingTime() {
        playerTimer = 0;
    }

    void TimeService::StepTime(const double delta) {
        mainTimer += delta;
        playerTimer += delta;
        if (mainTimer < 0) mainTimer = 0;
    }

}
