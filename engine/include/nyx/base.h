#pragma once

#ifdef NYX_DEBUG
    #if defined(NYX_PLATFORM_MSW)
        #define NYX_DEBUG_BREAK() __debugbreak()
    #elif defined(NYX_PLATFORM_UNIX)
        #include <signal.h>
        #define NYX_DEBUG_BREAK() raise(SIGTRAP)
    #else
        #error "Plaform does not support debug break"
    #endif
#else
    #define NYX_DEBUG_BREAK()
#endif

#define NYX_EXPAND_MACRO(x) x