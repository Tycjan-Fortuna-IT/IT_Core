#pragma once

#include <chrono>

#include "Logger.hpp"

namespace Core {
    class ProfilerTimer {
    public:

	    ProfilerTimer(const char* name)
		    : m_Name(name), m_Stopped(false) {
		    m_StartTimepoint = std::chrono::steady_clock::now();
	    }

	    ~ProfilerTimer() {
		    if (!m_Stopped)
			    Stop();
	    }

	    void Stop() {
		    const auto endTimepoint = std::chrono::steady_clock::now();
		    const auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

		    CORE_INFO("{0} took {1} us.", m_Name, elapsedTime.count());

		    m_Stopped = true;
	    }

    private:

	    const char* m_Name;
	    std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	    bool m_Stopped;
    };

    #define PROFILE_SCOPE(name) PROFILER_SCOPE_EXPANSION(name, __LINE__);

    #define PROFILER_SCOPE_EXPANSION(name, line) Core::ProfilerTimer timer##line(name);
											       
}
