//
// Created by Ahmed Mustafa on 6/30/2025.
//

#ifndef ITRIGGER_H
#define ITRIGGER_H

namespace SPI {

    class Application;

    class ITrigger {

    protected:
        Application* context = nullptr;

    public:
        explicit ITrigger(Application* context) : context(context) {}
        virtual ~ITrigger() = default;

        virtual bool IsActive() const = 0;
    };

}

#endif //ITRIGGER_H
