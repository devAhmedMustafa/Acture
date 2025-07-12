#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <pybind11/complex.h>

#include "engine/spich.h"

namespace py = pybind11;

using namespace pybind11::literals;

PYBIND11_MODULE(pystation, m) {

    // Main Application
    py::class_<SPI::Application>(m, "Engine")
        .def(py::init<>())
        .def("get_media_binder", &SPI::Application::GetMediaBinder, py::return_value_policy::reference)
        .def("get_station_network", &SPI::Application::GetStationNetwork, py::return_value_policy::reference)
        .def("get_current_time", &SPI::Application::GetCurrentTime)
        .def("play", &SPI::Application::Play)
        .def("travel", &SPI::Application::Travel, py::arg("thread"))
        .def("pause", &SPI::Application::Pause)
        .def("on_update", &SPI::Application::OnUpdate, py::arg("delta_time"))
        .def("rewind", &SPI::Application::Rewind)
        .def("receive_channel_data", &SPI::Application::ReceiveChannelData, py::return_value_policy::reference);

    // Deserializers
    py::class_<SPI::StationNetworkSerializer>(m, "StationNetworkSerializer")
        .def(py::init<SPI::Application*>())
        .def("import_spi_file", &SPI::StationNetworkSerializer::ImportSpiFile, py::arg("load_path"));


    // Clip
    py::class_<SPI::Clip, std::shared_ptr<SPI::Clip>>(m, "Clip")
        .def_readwrite("media_type", &SPI::Clip::mediaType)
        .def_readwrite("media_path", &SPI::Clip::mediaPath)
        .def("__bool__", &SPI::Clip::operator!)
        .def("to_dict", [](const SPI::Clip& self) {
            return py::dict(
                "media_type"_a = self.mediaType,
                "media_path"_a = self.mediaPath
            );
        });

    // VideoClip
    py::class_<SPI::VideoClip, std::shared_ptr<SPI::VideoClip>>(m, "VideoClip")
        .def(py::init<const std::string&, const itime_t, const itime_t>())
        .def_readwrite("start", &SPI::VideoClip::start)
        .def_readwrite("end", &SPI::VideoClip::end)
        .def("to_dict", [](const SPI::VideoClip& self) {
            return py::dict(
                "media_type"_a = (int)self.mediaType,
                "media_path"_a = self.mediaPath,
                "start"_a = self.start,
                "end"_a = self.end
            );
        });


    // Track
    py::class_<SPI::Track, std::shared_ptr<SPI::Track>>(m, "Track")
        .def(py::init<>())
        .def("add_clip", &SPI::Track::AddClip, py::arg("position"), py::arg("clip"))
        .def("remove_clip", &SPI::Track::RemoveClip, py::arg("position"))
        .def("clear_clips", &SPI::Track::ClearClips)
        .def("get_clip", &SPI::Track::GetClip, py::arg("position"), py::return_value_policy::reference)
        .def("get_length", &SPI::Track::GetLength)
        .def("get_media_type", &SPI::Track::GetMediaType)
        .def("set_media_type", &SPI::Track::SetMediaType, py::arg("type"))
        .def("get_clip_count", &SPI::Track::GetClipCount)
        .def_readwrite("clips", &SPI::Track::clips, py::return_value_policy::reference);

    // Verse
    py::class_<SPI::Verse, std::shared_ptr<SPI::Verse>>(m, "Verse")
        .def(py::init<>())
        .def("get_id", &SPI::Verse::GetID)
        .def("create_track", &SPI::Verse::CreateTrack)
        .def("delete_track", &SPI::Verse::DeleteTrack, py::arg("idx"))
        .def("calculate_length", &SPI::Verse::CalculateLength)
        .def("get_length", &SPI::Verse::GetLength)
        .def_readwrite("tracks", &SPI::Verse::tracks, py::return_value_policy::reference);


    // Station Network
    py::class_<SPI::StationNetwork>(m, "StationNetwork")
        .def(py::init<>())
        .def("get_root", &SPI::StationNetwork::GetRoot)
        .def("size", &SPI::StationNetwork::Size)
        .def("get_station_by_id", &SPI::StationNetwork::GetStationById, py::arg("id"), py::return_value_policy::reference);

    py::class_<SPI::MediaBinder>(m, "MediaBinder")
        .def(py::init<>())
        .def("bind_verse", &SPI::MediaBinder::BindVerse, py::arg("verse"))
        .def("unbind_verse", &SPI::MediaBinder::UnbindVerse)
        .def("get_verse", &SPI::MediaBinder::getVerse, py::return_value_policy::reference)
        .def("data_to_bind", &SPI::MediaBinder::DataToBind, py::arg("time"), py::return_value_policy::reference);

    py::enum_<SPI::MEDIA_TYPE>(m, "MEDIA_TYPE")
        .value("UNKNOWN", SPI::MEDIA_TYPE::UNKNOWN)
        .value("VIDEO", SPI::MEDIA_TYPE::VIDEO)
        .value("AUDIO", SPI::MEDIA_TYPE::AUDIO)
        .value("IMAGE", SPI::MEDIA_TYPE::IMAGE)
        .export_values();

    py::enum_<SPI::STATION_TYPE>(m, "STATION_TYPE")
        .value("ROOT", SPI::STATION_TYPE::ROOT)
        .value("LEAF", SPI::STATION_TYPE::LEAF)
        .value("HISTORY", SPI::STATION_TYPE::HISTORY)
        .value("MCQ", SPI::STATION_TYPE::MCQ);

    py::class_<SPI::Station, std::shared_ptr<SPI::Station>>(m, "Station")
        .def("get_id", &SPI::Station::GetId)
        .def("get_type", &SPI::Station::GetType)
        .def("get_lifetime", &SPI::Station::GetLifetime)
        .def("will_pause", &SPI::Station::WillPause)
        .def("get_connected_station", &SPI::Station::GetConnectedStation, py::arg("thread"))
        .def("get_connected_verse", &SPI::Station::GetConnectedVerse, py::arg("thread"))
        .def("get_all_connected_stations", &SPI::Station::GetAllConnectedStations, py::return_value_policy::reference)
        .def("get_all_connected_verses", &SPI::Station::GetAllConnectedVerses, py::return_value_policy::reference)
        .def("get_thread_count", &SPI::Station::getThreadCount);

    py::class_<SPI::StationChannelSchema, std::shared_ptr<SPI::StationChannelSchema>>(m, "StationChannelSchema")
        .def_readwrite("station_type", &SPI::StationChannelSchema::stationType)
        .def_readwrite("will_pause", &SPI::StationChannelSchema::willPause)
        .def_readwrite("lifetime", &SPI::StationChannelSchema::lifetime)
        .def("to_dict", [](const SPI::StationChannelSchema& self) {
            return py::dict(
                "station_type"_a = (int)self.stationType,
                "will_pause"_a = self.willPause,
                "lifetime"_a = self.lifetime
            );
        });

    py::class_<SPI::McqChannelSchema, std::shared_ptr<SPI::McqChannelSchema>, SPI::StationChannelSchema>(m, "McqChannelSchema")
        .def_readwrite("question", &SPI::McqChannelSchema::question)
        .def_readwrite("options", &SPI::McqChannelSchema::options)
        .def("to_dict", [](const SPI::McqChannelSchema& self) {
            return py::dict(
                "station_type"_a = (int)self.stationType,
                "will_pause"_a = self.willPause,
                "lifetime"_a = self.lifetime,
                "question"_a = self.question,
                "options"_a = self.options
            );
        });
        
}

