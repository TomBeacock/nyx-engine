#pragma once

#include "base.h"
#include "log.h"

#ifdef NYX_DEBUG
    #define NYX_INTERNAL_ASSERT_IMPL(source, check, msg, ...)                  \
        {                                                                      \
            if (!(check)) {                                                    \
                NYX##source##ERROR(msg, __VA_ARGS__);                          \
                NYX_DEBUG_BREAK();                                             \
            }                                                                  \
        }
    #define NYX_INTERNAL_ASSERT(source, check, ...)                            \
        NYX_INTERNAL_ASSERT_IMPL(source, check, "Assertion failed")
    #define NYX_INTERNAL_ASSERT_MSG(source, check, ...)                        \
        NYX_INTERNAL_ASSERT_IMPL(source, check, __VA_ARGS__)

    #define NYX_INTERNAL_ASSERT_GET_NAME(...)                                  \
        NYX_EXPAND_MACRO(NYX_INTERNAL_ASSERT##__VA_OPT__(_MSG))

    #define NYX_ASSERT(check, ...)                                             \
        NYX_EXPAND_MACRO(NYX_INTERNAL_ASSERT_GET_NAME(__VA_ARGS__))            \
        (_, check, __VA_ARGS__)
    #define NYX_ENGINE_ASSERT(check, ...)                                      \
        NYX_EXPAND_MACRO(NYX_INTERNAL_ASSERT_GET_NAME(__VA_ARGS__))            \
        (_ENGINE_, check, __VA_ARGS__)

#else
    #define NYX_ASSERT(...)
#endif