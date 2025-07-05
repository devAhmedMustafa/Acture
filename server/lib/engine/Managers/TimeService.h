//
// Created by am180 on 3/6/2025.
//

#ifndef INTRASTATION_VERSETIMELINE_H
#define INTRASTATION_VERSETIMELINE_H

namespace SPI {

    class TimeService {

        double mainTimer = 0.0;
        double playerTimer = 0.0;
        double lastTime = 0.0;

        static TimeService* instance;

    public:

        static TimeService& Get() {return *instance;}

        TimeService();
        ~TimeService();

        void SetTime(double newTime);

        double GetMainTime() const { return mainTimer; }
        double GetPlayerTime() const { return playerTimer; }

        void ResetPlayingTime();

        void StepTime(double delta);
        void SetLastTime(const double lastTime) { this->lastTime = lastTime; }

    };

}



#endif //INTRASTATION_VERSETIMELINE_H
