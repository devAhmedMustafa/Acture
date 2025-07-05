//
// Created by Ahmed Mustafa on 4/30/2025.
//

#ifndef EVENT_H
#define EVENT_H

#include <vector>
#include <functional>

namespace SPI {

    template<class T>
    using Callback = std::function<void(std::shared_ptr<T>)>;

    template<class T>
    class Event {

        std::vector<Callback<T>> callbacks;

    public:

        void Subscribe(Callback<T> callback) {
            callbacks.push_back(callback);
        }

        void Dispatch(std::shared_ptr<T> data) {
            for (const auto& callback : callbacks) {
                callback(data);
            }
        }

    };

}

#endif //EVENT_H
