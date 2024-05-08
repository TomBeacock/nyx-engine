#pragma once

#include <format>
#include <iostream>
#include <string>

#ifdef NYX_LOGGING_ENABLED
#define NYX_LOG(msg)                                                           \
    std::cout << "\x1B[37m"                                                    \
              << std::format("{} ({}): Info: ", __FILE__ + SOURCE_PATH_LENGTH, \
                     __LINE__)                                                 \
              << msg << "\x1B[0m" << std::endl
#define NYX_WARN(msg)                                                          \
    std::cout << "\x1B[33m"                                                    \
              << std::format("{} ({}): Warn: ", __FILE__ + SOURCE_PATH_LENGTH, \
                     __LINE__)                                                 \
              << msg << "\x1B[0m" << std::endl
#define NYX_ERROR(msg)                                                         \
    std::cout << "\x1B[31m"                                                    \
              << std::format("{} ({}): Error: ",                               \
                     __FILE__ + SOURCE_PATH_LENGTH, __LINE__)                  \
              << msg << "\x1B[0m" << std::endl
#define NYX_LOG_F(fmt, ...)                                                    \
    std::cout << "\x1B[37m"                                                    \
              << std::format("{} ({}): Info: ", __FILE__ + SOURCE_PATH_LENGTH, \
                     __LINE__)                                                 \
              << std::format(fmt __VA_OPT__(, ) __VA_ARGS__) << "\x1B[0m"      \
              << std::endl
#define NYX_WARN_F(fmt, ...)                                                   \
    std::cout << "\x1B[33m"                                                    \
              << std::format("{} ({}): Warn: ", __FILE__ + SOURCE_PATH_LENGTH, \
                     __LINE__)                                                 \
              << std::format(fmt __VA_OPT__(, ) __VA_ARGS__) << "\x1B[0m"      \
              << std::endl
#define NYX_ERROR_F(fmt, ...)                                                  \
    std::cout << "\x1B[31m" << std::format(fmt __VA_OPT__(, ) __VA_ARGS__)     \
              << std::format("{} ({}): Error: ",                               \
                     __FILE__ + SOURCE_PATH_LENGTH, __LINE__)                  \
              << "\x1B[0m" << std::endl
#else
#define NYX_LOG(...)
#define NYX_WARN(...)
#define NYX_ERROR(...)
#define NYX_LOG_F(...)
#define NYX_WARN_F(...)
#define NYX_ERROR_F(...)
#endif