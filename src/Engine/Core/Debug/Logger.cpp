#include "pch.hpp"
#include "Logger.hpp"

namespace Core {
    std::shared_ptr<spdlog::logger> s_AppLogger{ nullptr };
    std::shared_ptr<spdlog::logger> s_CoreLogger{ nullptr };

    void Logger::Init() {
        std::vector<spdlog::sink_ptr> coreLogSinks;
        std::vector<spdlog::sink_ptr> appLogSinks;

        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        consoleSink->set_pattern("%^[%T] %n: %v%$");

        auto coreFileSink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/CORE.log", 0, 0);
        coreFileSink->set_pattern("[%T] [%l] %n: %v");

        auto appFileSink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/APP.log", 0, 0);
        appFileSink->set_pattern("[%T] [%l] %n: %v");

        coreLogSinks.emplace_back(consoleSink);
        coreLogSinks.emplace_back(coreFileSink);

        appLogSinks.emplace_back(consoleSink);
        appLogSinks.emplace_back(appFileSink);

        s_CoreLogger = std::make_shared<spdlog::logger>("CORE", begin(coreLogSinks), end(coreLogSinks));
        s_CoreLogger->set_level(spdlog::level::trace);
        s_CoreLogger->flush_on(spdlog::level::trace);

        s_AppLogger = std::make_shared<spdlog::logger>("APP", begin(appLogSinks), end(appLogSinks));
        s_AppLogger->set_level(spdlog::level::trace);
        s_AppLogger->flush_on(spdlog::level::trace);

        spdlog::register_logger(s_CoreLogger);
        spdlog::register_logger(s_AppLogger);
    }

    void Logger::Shutdown() {
        s_CoreLogger.reset();
        s_AppLogger.reset();

        spdlog::drop_all();
    }
}
