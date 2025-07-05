//
// Created by am180 on 3/4/2025.
//

#include "Track.h"

#include <iostream>
#include <ranges>
#include <functional>

#include "VideoClip.h"

namespace SPI {

    Track::Track() : length(0.0) {}
    Track::~Track() {
        for (auto& clip : clips) {
            if (clip.second) {
                clip.second.reset();
            }
        }
    }

    void Track::AddClip(itime_t position, const std::shared_ptr<Clip>& clip) {
        clips.insert({position, clip});
        CalculateLength();
    }

    void Track::RemoveClip(const itime_t position) {
        if (const auto it = clips.find(position); it != clips.end()) {
            clips.erase(it);
        }

        CalculateLength();
    }

    void Track::ClearClips() {
        clips.clear();

        CalculateLength();
    }

    std::shared_ptr<Clip> Track::GetClip(const itime_t position) const {
        auto it = clips.find(position);
        if (it != clips.end()) {
            return it->second;
        }
        throw std::out_of_range("Clip not found at the specified position.");
    }

    itime_t Track::CalculateLength() {
        const auto lastClip = clips.rbegin();

        if (lastClip->second->mediaType == MEDIA_TYPE::VIDEO) {
            const auto videoClip = std::reinterpret_pointer_cast<VideoClip>(lastClip->second);
            length = lastClip->first + videoClip->end - videoClip->start;
        }
        else {
            length = -1;
        }

        return length;
    }

}
