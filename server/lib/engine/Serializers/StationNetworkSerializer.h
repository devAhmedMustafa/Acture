//
// Created by Ahmed Mustafa on 5/2/2025.
//

#ifndef APPSERIALIZER_H
#define APPSERIALIZER_H

#include <string>
#include <fstream>
#include <queue>

#include "AssetSerializer.h"
#include "../Application.h"
#include "../Stores/StationNetwork.h"

namespace SPI {

    class StationNetworkSerializer {

        Application *app;
        StationNetwork* network;
        std::fstream fStream;
        std::string path;

        std::queue<std::streampos> stations_positions;
        std::queue<std::streampos> videos_positions;

        std::streampos firstvideo_position;

        ASSETS_MODE assetMode = ASSETS_MODE::BUNDLE;

        void SerializeNetwork(std::ostream& out);
        void DeserializeNetwork();

        void MapSerialize(std::ostream& out, bool verseMode);
        StationNetwork* MapDeserialize(std::istream& in);


    public:
        explicit StationNetworkSerializer(Application*);

        void ExportSpiFile(const std::string& savePath);
        std::vector<uint8_t> ExportSpiBuffer();
        void ImportSpiFile(const std::string& loadPath);

        void SetAssetMode(const ASSETS_MODE mode) {
            this->assetMode = mode;
        }

        location_t GetFirstVideoPosition() const {
            return this->firstvideo_position;
        }

    };

}


#endif //APPSERIALIZER_H
