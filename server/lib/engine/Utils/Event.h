//
// Created by Ahmed Mustafa on 3/9/2025.
//

#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <string>

namespace SPI {

    class Event {
    public:
        virtual ~Event() = default;
    };

    class EventDispatcher {

        using EventCallback = std::function<void(Event&)>;
        std::unordered_map<std::string, std::vector<EventCallback>> listeners;

    public:

        void Subscribe(const std::string& event, EventCallback callback) {
            listeners[event].push_back(callback);
        }

        void Dispatch(const std::string& event, Event& e) {
            if (listeners.find(event) != listeners.end()) {
                for (auto& callback : listeners[event]) {
                    callback(e);
                }
            }
        }

    };

}

#endif //EVENT_H
