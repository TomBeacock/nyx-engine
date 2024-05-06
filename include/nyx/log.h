#pragma once

#include <format>
#include <iostream>
#include <string>

#ifdef NYX_LOGGING_ENABLED
#define NYX_LOG(fmt, ...)                                                      \
    std::cout << "\x1B[37mINFO: "                                              \
              << std::format(fmt __VA_OPT__(, ) __VA_ARGS__)                   \
              << std::format("\n[{}, Ln: {}]", __FILE__ + SOURCE_PATH_LENGTH,  \
                     __LINE__)                                                 \
              << "\x1B[0m" << std::endl
#define NYX_WARN(fmt, ...)                                                     \
    std::cout << "\x1B[33mWARN: "                                              \
              << std::format(fmt __VA_OPT__(, ) __VA_ARGS__)                   \
              << std::format("\n[{}, Ln: {}]", __FILE__ + SOURCE_PATH_LENGTH,  \
                     __LINE__)                                                 \
              << "\x1B[0m" << std::endl
#define NYX_ERROR(fmt, ...)                                                    \
    std::cout << "\x1B[31mERROR: "                                             \
              << std::format(fmt __VA_OPT__(, ) __VA_ARGS__)                   \
              << std::format("\n[{}, Ln: {}]", __FILE__ + SOURCE_PATH_LENGTH,  \
                     __LINE__)                                                 \
              << "\x1B[0m" << std::endl
#else
#define NYX_LOG(...)
#define NYX_WARN(...)
#define NYX_ERROR(...)
#endif