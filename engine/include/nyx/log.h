#pragma once

#include <format>
#include <iostream>
#include <string>

#if defined(NYX_DEBUG) || defined(NYX_DEBUG_INFO_ONLY)
    #define NYX_INTERNAL_LOG_IMPL(type, color, source, msg, ...)               \
        std ::cout << "\x1B[" #color "m"                                       \
                   << std::format("{} ({}):" #type ": ",                       \
                          __FILE__ + NYX_##source##_SOURCE_PATH_LENGTH,        \
                          __LINE__)                                            \
                   << std::format(msg __VA_OPT__(, ) __VA_ARGS__) << "\x1B[0m" \
                   << std::endl

    #define NYX_INFO(msg, ...)                                                 \
        NYX_INTERNAL_LOG_IMPL(Info, 37, PROJECT, msg, __VA_ARGS__)
    #define NYX_WARN(msg, ...)                                                 \
        NYX_INTERNAL_LOG_IMPL(Warn, 33, PROJECT, msg, __VA_ARGS__)
    #define NYX_ERROR(msg, ...)                                                \
        NYX_INTERNAL_LOG_IMPL(Error, 31, PROJECT, msg, __VA_ARGS__)

    #define NYX_ENGINE_INFO(msg, ...)                                          \
        NYX_INTERNAL_LOG_IMPL(Info, 37, ENGINE, msg, __VA_ARGS__)
    #define NYX_ENGINE_WARN(msg, ...)                                          \
        NYX_INTERNAL_LOG_IMPL(Warn, 33, ENGINE, msg, __VA_ARGS__)
    #define NYX_ENGINE_ERROR(msg, ...)                                         \
        NYX_INTERNAL_LOG_IMPL(Error, 31, ENGINE, msg, __VA_ARGS__)
#else
    #define NYX_INFO(...)
    #define NYX_WARN(...)
    #define NYX_ERROR(...)
    #define NYX_ENGINE_INFO(...)
    #define NYX_ENGINE_WARN(...)
    #define NYX_ENGINE_ERROR(...)
#endif