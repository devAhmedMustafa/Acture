//
// Created by Ahmed Mustafa on 5/1/2025.
//

#ifndef STATIONCHANNEL_H
#define STATIONCHANNEL_H

#include <utility>

#include "Channel.h"
#include "../Events/StationCallEvent.h"
#include "../Schemas/StationChannelSchema.h"

namespace SPI {

    class StationChannel final : public Channel<StationChannelSchema> {

    public:
        explicit StationChannel(StationCallEvent & event) {
            event.Subscribe([&](std::shared_ptr<StationChannelSchema> data) {
                this->data = std::move(data);
                notified = true;
            });
        }

        ~StationChannel() override = default;

        void Send(std::shared_ptr<StationChannelSchema> data) override {}

    };

}

#endif //STATIONCHANNEL_H
