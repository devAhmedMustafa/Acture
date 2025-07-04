#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <pybind11/complex.h>

#include "engine/spich.h"

namespace py = pybind11;

PYBIND11_MODULE(pystation, m) {

    // Main Application
    py::class_<SPI::Application>(m, "Engine")
        .def(py::init<>())
        .def("get_media_binder", &SPI::Application::GetMediaBinder, py::return_value_policy::reference)
        .def("get_station_network", &SPI::Application::GetStationNetwork, py::return_value_policy::reference)
        .def("get_current_time", &SPI::Application::GetCurrentTime)
        .def("play", &SPI::Application::Play)
        .def("pause", &SPI::Application::Pause)
        .def("rewind", &SPI::Application::Rewind);

    // Deserializers
    py::class_<SPI::StationNetworkSerializer>(m, "StationNetworkSerializer")
        .def(py::init<SPI::Application*>())
        .def("import_spi_file", &SPI::StationNetworkSerializer::ImportSpiFile, py::arg("load_path"));


    // Clip
    py::class_<SPI::Clip>(m, "Clip")
        .def_readwrite("media_type", &SPI::Clip::mediaType)
        .def_readwrite("media_path", &SPI::Clip::mediaPath)
        .def("__bool__", &SPI::Clip::operator!);

    // VideoClip
    py::class_<SPI::VideoClip, SPI::Clip>(m, "VideoClip")
        .def(py::init<const std::string&, const itime_t, const itime_t>())
        .def_readwrite("start", &SPI::VideoClip::start)
        .def_readwrite("end", &SPI::VideoClip::end);


    // Track
    py::class_<SPI::Track>(m, "Track")
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
    py::class_<SPI::Verse>(m, "Verse")
        .def(py::init<>())
        .def("create_track", &SPI::Verse::CreateTrack)
        .def("delete_track", &SPI::Verse::DeleteTrack, py::arg("idx"))
        .def("calculate_length", &SPI::Verse::CalculateLength)
        .def("get_length", &SPI::Verse::GetLength)
        .def_readwrite("tracks", &SPI::Verse::tracks, py::return_value_policy::reference);


    // Station Network
    py::class_<SPI::StationNetwork>(m, "StationNetwork")
        .def(py::init<>())
        .def("get_root", &SPI::StationNetwork::GetRoot)
        .def("size", &SPI::StationNetwork::Size);

    py::class_<SPI::MediaBinder>(m, "MediaBinder")
        .def(py::init<>())
        .def("bind_verse", &SPI::MediaBinder::BindVerse, py::arg("verse"))
        .def("unbind_verse", &SPI::MediaBinder::UnbindVerse)
        .def("get_verse", &SPI::MediaBinder::getVerse, py::return_value_policy::reference)
        .def("data_to_bind", &SPI::MediaBinder::DataToBind, py::arg("time"), py::return_value_policy::reference);



}

