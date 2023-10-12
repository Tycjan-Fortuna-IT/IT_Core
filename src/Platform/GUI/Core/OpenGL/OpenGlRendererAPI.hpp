#pragma once

#include <glm/glm.hpp>

namespace Core {
    class OpenGlRendererAPI final {
    public:
        static void Init();

        static void SetClearColor(const glm::vec4& color);
        static void Clear();
    };
}
