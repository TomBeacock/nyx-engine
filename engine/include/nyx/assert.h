#pragma once

#include "log.h"

#ifdef NYX_ASSERTS_ENABLED
#define NYX_ASSERT(check, message, ...)                                        \
    {                                                                          \
        if (!(check)) {                                                        \
            NYX_ERROR(message __VA_OPT__(, ) __VA_ARGS__);                     \
        }                                                                      \
    }
#else
#define ASSERT(...)
#endif