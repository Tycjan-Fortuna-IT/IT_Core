#pragma once

#include <memory>

#include "Engine/Core/Base.hpp"

#include <spdlog/spdlog.h>
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#ifdef CORE_DEBUG
    #define CORE_TRACE(...)       ::Core::Logger::GetCoreLogger()->trace(__VA_ARGS__)
    #define CORE_INFO(...)        ::Core::Logger::GetCoreLogger()->info(__VA_ARGS__)
    #define CORE_WARN(...)        ::Core::Logger::GetCoreLogger()->warn(__VA_ARGS__)
    #define CORE_ERROR(...)       ::Core::Logger::GetCoreLogger()->error(__VA_ARGS__)
    #define CORE_CRITICAL(...)    ::Core::Logger::GetCoreLogger()->critical(__VA_ARGS__); DEBUG_BREAK()

    #define APP_TRACE(...)        ::Core::Logger::GetAppLogger()->trace(__VA_ARGS__)
    #define APP_INFO(...)         ::Core::Logger::GetAppLogger()->info(__VA_ARGS__)
    #define APP_WARN(...)         ::Core::Logger::GetAppLogger()->warn(__VA_ARGS__)
    #define APP_ERROR(...)        ::Core::Logger::GetAppLogger()->error(__VA_ARGS__)
    #define APP_CRITICAL(...)     ::Core::Logger::GetAppLogger()->critical(__VA_ARGS__); DEBUG_BREAK()
#elif CORE_RELEASE
    #define CORE_TRACE(...)
    #define CORE_INFO(...)
    #define CORE_WARN(...)        ::Core::Logger::GetCoreLogger()->warn(__VA_ARGS__)
    #define CORE_ERROR(...)       ::Core::Logger::GetCoreLogger()->error(__VA_ARGS__)
    #define CORE_CRITICAL(...)    ::Core::Logger::GetCoreLogger()->critical(__VA_ARGS__); DEBUG_BREAK()

    #define APP_TRACE(...)
    #define APP_INFO(...)
    #define APP_WARN(...)         ::Core::Logger::GetAppLogger()->warn(__VA_ARGS__)
    #define APP_ERROR(...)        ::Core::Logger::GetAppLogger()->error(__VA_ARGS__)
    #define APP_CRITICAL(...)     ::Core::Logger::GetAppLogger()->critical(__VA_ARGS__); DEBUG_BREAK()
#else
    #define CORE_TRACE(...)
    #define CORE_INFO(...)
    #define CORE_WARN(...)
    #define CORE_ERROR(...)       ::Core::Logger::GetCoreLogger()->error(__VA_ARGS__)
    #define CORE_CRITICAL(...)    ::Core::Logger::GetCoreLogger()->critical(__VA_ARGS__); DEBUG_BREAK()

    #define APP_TRACE(...)
    #define APP_INFO(...)
    #define APP_WARN(...)
    #define APP_ERROR(...)        ::Core::Logger::GetAppLogger()->error(__VA_ARGS__)
    #define APP_CRITICAL(...)     ::Core::Logger::GetAppLogger()->critical(__VA_ARGS__); DEBUG_BREAK()
#endif

#ifdef CORE_PLATFORM_WINDOWS
    #define DEBUG_BREAK() __debugbreak()
#elif defined(CORE_PLATFORM_LINUX)
    #include <signal.h>
    #define DEBUG_BREAK() raise(SIGTRAP)
#else
    #error "Platform not supported!"
#endif

#ifdef ENABLE_ASSERTS
    #define ASSERT(check, ...)    { if (!(check)) { CORE_CRITICAL(__VA_ARGS__); DEBUG_BREAK(); } }
#else
    #define ASSERT(...)
#endif

namespace Core {
    enum LogLevel : uint32_t {
        Trace = 1,
        Debug = 2,
        Info = 4,
        Warn = 8,
        Error = 16,
        Critical = 32,
    };

    class Logger final {
    public:

        static void Init();
        static void Shutdown();

        static std::shared_ptr<spdlog::logger> GetAppLogger() { return s_AppLogger; }
        static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }

    private:

        inline static std::shared_ptr<spdlog::logger> s_AppLogger{ nullptr };
        inline static std::shared_ptr<spdlog::logger> s_CoreLogger{ nullptr };
    };
}

