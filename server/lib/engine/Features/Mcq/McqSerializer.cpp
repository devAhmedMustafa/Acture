//
// Created by Ahmed Mustafa on 5/2/2025.
//

#include "McqSerializer.h"

#include "../MCQStation.h"

namespace SPI {

    McqSerializer::McqSerializer(std::ostream& out, std::istream& in)
        : StationSerializer(out, in) {}

    void McqSerializer::SerializeBody() {
        const auto& mcq = std::dynamic_pointer_cast<MCQStation>(station);

        const auto question = mcq->getQuestion();
        const uint32_t questionSize = question.size();

        out.write(reinterpret_cast<const char *>(&questionSize), sizeof(questionSize));
        out.write(question.c_str(), questionSize);

        const uint32_t optionsCount = mcq->getOptions().size();
        out.write(reinterpret_cast<const char *>(&optionsCount), sizeof(optionsCount));

        for (int i = 0; i < optionsCount; ++i) {
            const auto& option = mcq->getOption(i);
            const auto optionSize = static_cast<uint32_t>(option.length());
            out.write(reinterpret_cast<const char *>(&optionSize), sizeof(optionSize));
            out.write(option.c_str(), optionSize);
        }
    }

    void McqSerializer::DeserializeBody() {
        const auto& mcq = std::dynamic_pointer_cast<MCQStation>(station);
        uint32_t questionSize;
        in.read(reinterpret_cast<char *>(&questionSize), sizeof(questionSize));
        std::string question(questionSize, '\0');
        in.read(&question[0], questionSize);

        mcq->setQuestion(question);

        uint32_t optionsCount;
        in.read(reinterpret_cast<char *>(&optionsCount), sizeof(optionsCount));

        for (uint32_t i = 0; i < optionsCount; ++i) {
            uint32_t optionSize;
            in.read(reinterpret_cast<char *>(&optionSize), sizeof(optionSize));

            std::string option(optionSize, '\0');
            in.read(&option[0], optionSize);
            mcq->setOption(i, option);
        }

    }

}
