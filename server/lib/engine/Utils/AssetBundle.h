//
// Created by Ahmed Mustafa on 7/2/2025.
//

#ifndef ASSETBUNDLE_H
#define ASSETBUNDLE_H

#include <string>
#include <iostream>
#include <fstream>
#include "../Core/Core.h"
#include <vector>

namespace SPI {

    class AssetBundle {
    public:
        static void CreateBundle(std::ostream& out, const std::string& assetPath) {
            std::cout << "Writing video file: " << assetPath << std::endl;

            std::ifstream file(assetPath, std::ios::binary);
            if (!file.is_open()) {
                std::cout << "Failed to open video file: " << assetPath << std::endl;
                throw std::runtime_error("Failed to open video file");
            }

            file.seekg(0, std::ios::end);
            const location_t fileSize = file.tellg();

            if (fileSize == -1) {
                throw std::runtime_error("Failed to get video file size");
            }

            file.seekg(0, std::ios::beg);

            out.write(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize));

            std::vector<char> buffer(fileSize);
            if (!file.read(buffer.data(), fileSize)) {
                throw std::runtime_error("Failed to read video file");
            }

            out.write(buffer.data(), fileSize);

            file.close();
        }
    };

}

#endif //ASSETBUNDLE_H
