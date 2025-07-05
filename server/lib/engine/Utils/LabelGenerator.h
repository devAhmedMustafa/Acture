
#pragma once


#include <string>
#include <map>

namespace SPI {

    class LabelGenerator {

    public:
        static std::map<std::string, int> labelCount;

        static std::string generateLabel(const std::string &label) {
            if (labelCount.find(label) == labelCount.end()) {
                labelCount[label] = 0;
            }
            return label + std::to_string(labelCount[label]++);
        }
    };

}

