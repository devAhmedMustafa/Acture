//
// Created by Ahmed Mustafa on 5/2/2025.
//

#include <sstream>

#include "StationNetworkSerializer.h"

#include "AssetSerializer.h"
#include "../Mappers/StationSerialzerMapper.h"
#include "Units/VideoClip.h"


namespace SPI {

    // Exporting

    StationNetworkSerializer::StationNetworkSerializer(Application* app) : app(app), network(app->GetStationNetwork()) {}

    void StationNetworkSerializer::ExportSpiFile(const std::string &savePath) {
        std::ofstream fileStream;
        fileStream.open(savePath, std::ios::out | std::ios::binary);

        if (!fileStream.is_open()) {
            throw std::runtime_error("Failed to open file for writing");
        }

        this->SerializeNetwork(fileStream);

        fileStream.close();
        std::cout << "File saved successfully at " << savePath << std::endl;
    }

    std::vector<uint8_t> StationNetworkSerializer::ExportSpiBuffer() {
        std::ostringstream oss;
        this->SerializeNetwork(oss);
        std::string str = oss.str();
        std::vector<uint8_t> buffer(str.begin(), str.end());
        return buffer;
    }


    void StationNetworkSerializer::SerializeNetwork(std::ostream& out) {

        const location_t location = 0;
        this->firstvideo_position = out.tellp();
        out.write(reinterpret_cast<const char*>(&location), sizeof(location_t));
        const auto nStations = network->Size();
        out.write(reinterpret_cast<const char*>(&nStations), sizeof(stations_size_t));

        MapSerialize(out, false);
        MapSerialize(out, true);

    }

    void StationNetworkSerializer::MapSerialize(std::ostream& out, const bool verseMode) {
        for (const auto& station : network->GetAllStations()) {
            if (!verseMode) {
                const auto station_serializer = CreateStationSerializer(station->GetType(), out, this->fStream, app);
                station_serializer->Serialize(station);
            }

            for (auto i = 0; i < station->getThreadCount(); i++) {
                if (verseMode) {
                    const location_t videoLocation = out.tellp();

                    out.seekp(videos_positions.front());
                    out.write(reinterpret_cast<const char *>(&videoLocation), sizeof(location_t));
                    videos_positions.pop();

                    if (station->GetId() == 0) {
                        out.seekp(this->firstvideo_position);
                        out.write(reinterpret_cast<const char *>(&videoLocation), sizeof(location_t));
                    }

                    out.seekp(videoLocation);

                    AssetSerializer assetSerializer(out, this->assetMode);
                    assetSerializer.Serialize(station->GetConnectedVerse(i)->tracks[0]->clips[0].get());
                }
                else {
                    location_t location = 0;
                    videos_positions.push(out.tellp());
                    out.write(reinterpret_cast<const char *>(&location), sizeof(location_t));
                }

            }
        }
    }



    // Importing

    void StationNetworkSerializer::ImportSpiFile(const std::string &loadPath) {

        if (this->fStream.is_open()) {
            this->fStream.close();
        }

        this->fStream.open(loadPath, std::ios::in | std::ios::binary);
        if (!this->fStream.is_open()) {
            throw std::runtime_error("Failed to open file for reading");
        }

        this->path = loadPath;

        DeserializeNetwork();

        fStream.close();

        app->GetStationManager()->network = network;
        app->GetStationManager()->prevStation = network->GetRoot();
        app->GetStationManager()->nextStation = network->GetRoot();

        app->Travel(0);
        app->TranslateState(EngineState::PAUSED);

    }

    void StationNetworkSerializer::DeserializeNetwork() {

        delete network;

        location_t firstVideoLocation;
        this->fStream.read(reinterpret_cast<char*>(&firstVideoLocation), sizeof(location_t));

        this->firstvideo_position = firstVideoLocation;

        network = MapDeserialize(fStream);
    }

    StationNetwork* StationNetworkSerializer::MapDeserialize(std::istream &in) {

        auto* network = new StationNetwork();

        stations_size_t nStations;
        in.read(reinterpret_cast<char*>(&nStations), sizeof(stations_size_t));

        while (nStations--) {
            STATION_TYPE type;
            // Read the station type
            in.read(reinterpret_cast<char*>(&type), sizeof(uint8_t));

            // Read the station data
            const auto station_serializer = CreateStationSerializer(type, this->fStream, in, app);
            const auto station = station_serializer->Deserialize(type);

            network->AddStation(station);

            if (station->GetId() == 0) {
                network->root = std::dynamic_pointer_cast<RootStation>(station);
            }

            for (auto j = 0; j < station->getThreadCount(); j++) {
                location_t position;
                in.read(reinterpret_cast<char*>(&position), sizeof(location_t));
                videos_positions.emplace(position);
            }
        }

        for (const auto& station : network->GetAllStations()) {
            for (auto i = 0; i < station->getThreadCount(); i++) {
                const auto child = network->GetStationById(station->GetConnectedStation(i));
                station->ConnectStation(i, child);

                location_t video_pos;
                in.read(reinterpret_cast<char*>(&video_pos), sizeof(location_t));

                const auto verse = station->GetConnectedVerse(i);

                verse->CreateTrack();
                // const auto clip = new VideoClip{this->path+"/"+std::to_string(video_pos), 0, child->GetTimelapse()};
                const auto clip = VideoClip{this->path, 0, child->GetTimelapse()};

                verse->tracks[0]->AddClip(0, std::make_shared<VideoClip>(clip));

            }
        }

        return network;

    }


}
