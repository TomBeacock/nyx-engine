#pragma once

#include "log.h"

#ifdef NYX_ASSERTS_ENABLED
#define NYX_ASSERT(check, msg)                                                 \
    {                                                                          \
        if (!(check)) {                                                        \
            NYX_ERROR(msg);                                                    \
        }                                                                      \
    }
#define NYX_ASSERT_F(check, fmt, ...)                                          \
    {                                                                          \
        if (!(check)) {                                                        \
            NYX_ERROR_F(fmt __VA_OPT__(, ) __VA_ARGS__);                       \
        }                                                                      \
    }
#else
#define ASSERT(...)
#endif