#pragma once

#include <string>
#include <vector>
#include "custom-types/shared/coroutine.hpp"
#include "sdc-wrapper/shared/BeatStarSong.hpp"

namespace BetterSongList::SongDetails {
    bool get_isAvailable();
    bool get_finishedInitAttempt();
    bool get_attemptedToInit();
    
    bool CheckAvailable();
    std::string GetUnavailabilityReason();
    custom_types::Helpers::Coroutine TryGet(std::function<void()> onFinished = nullptr);
    const std::vector<const SDC_wrapper::BeatStarSong*>& get_songDetails();
}