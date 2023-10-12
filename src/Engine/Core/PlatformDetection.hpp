#pragma once

#ifdef _WIN32
    #ifdef _WIN64
        #define CORE_PLATFORM_WINDOWS
    #else
        #error "Architecture not supported!"
    #endif
#elif defined(__linux__)
    #define CORE_PLATFORM_LINUX
#else
    #error "System not supported!"
#endif
