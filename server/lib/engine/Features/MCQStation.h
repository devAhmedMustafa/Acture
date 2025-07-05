//
// Created by Ahmed Mustafa on 3/5/2025.
//

#ifndef MCQSTATION_H
#define MCQSTATION_H

#include "../Machines/Station.h"

using str = std::string;

namespace SPI {

    class MCQStation final : public Station {

        str question;
        std::vector<str> options;

    public:
        explicit MCQStation() : Station(STATION_TYPE::MCQ) {}

        std::shared_ptr<Station> self() override { 
            return std::static_pointer_cast<Station>(shared_from_this()); 
        }

        str getQuestion() const { return question; }
        void setQuestion(const str &question) { this->question = question; }

        std::vector<str> getOptions() { return options; }
        std::string getOption(const size_t idx) const {
            if (idx >= options.size()) return "";
            return options[idx];
        }
        void setOption(const size_t idx, const str& newOption) { 
            if (idx >= options.size()) options.push_back(newOption);
            this->options[idx] = newOption;
        }
    };

}

#endif //MCQSTATION_H
