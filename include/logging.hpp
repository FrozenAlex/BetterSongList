#pragma once
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"
#include <string_view>

#include "paper2_scotland2/shared/logger.hpp"

template <> struct fmt::formatter<::StringW> : formatter<string_view> {
    // parse is inherited from formatter<string_view>.
    template <typename FormatContext>
    auto format(StringW s, FormatContext& ctx) {
        return formatter<string_view>::format(s ? static_cast<std::string>(s) : "NULL", ctx);
    }
};

namespace BSLLogger {
    static constexpr auto Logger = Paper::ConstLoggerContext(MOD_ID);
}

#define INFO(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::INF>(str, MOD_ID __VA_OPT__(, __VA_ARGS__))
#define ERROR(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::ERR>(str, MOD_ID __VA_OPT__(, __VA_ARGS__))
#define CRITICAL(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::ERR>(str, MOD_ID __VA_OPT__(, __VA_ARGS__))
#define DEBUG(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::DBG>(str, MOD_ID __VA_OPT__(, __VA_ARGS__))
#define WARNING(str, ...) Paper::Logger::fmtLogTag<Paper::LogLevel::WRN>(str, MOD_ID __VA_OPT__(, __VA_ARGS__))
