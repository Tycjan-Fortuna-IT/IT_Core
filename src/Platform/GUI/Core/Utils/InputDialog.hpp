#pragma once

#include <string>

namespace AI {
    class InputDialog final {
    public:

        static std::string OpenFileDialog(const char* filter);
    };
}
