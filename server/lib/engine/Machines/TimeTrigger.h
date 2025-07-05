//
// Created by Ahmed Mustafa on 7/1/2025.
//

#ifndef TIMETRIGGER_H
#define TIMETRIGGER_H

#include "ITrigger.h"

namespace SPI {

    class TimeTrigger : public ITrigger {
        float callingThreshold; // Threshold in seconds to trigger the action
    public:
        explicit TimeTrigger(Application* context, const float threshold = 0.01f)
            : ITrigger(context), callingThreshold(threshold) {}

        ~TimeTrigger() override = default;
        bool IsActive() const override;
    };

}



#endif //TIMETRIGGER_H
