#pragma once

namespace Core {
	class StringUtils {
	public:

		[[nodiscard]] static const char* FromChar8T(const char8_t* c)
		{
			return reinterpret_cast<const char*>(c);
		}
	};
}
