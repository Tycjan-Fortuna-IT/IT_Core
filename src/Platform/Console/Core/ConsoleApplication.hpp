#pragma once
#include <string>

#include "Engine/Core/Layer.hpp"
#include "Engine/Core/LayerStack.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv);

namespace Core {
    enum class ApplicationType {
        Window,
        Console
    };

    struct ApplicationCommandArguments final {
        int Argc{ 0 };
        char** Argv{ nullptr };
    };

    struct ApplicationSpecification final {
        std::string Name{ "Core Application" };
        ApplicationType Type{ ApplicationType::Console };
        uint32_t Width{ 0 }; // If Type is Window, Width and Height are required
        uint32_t Height{ 0 };
        ApplicationCommandArguments CommandArguments; // If Type is Console, CommandArguments are required
    };

    class Application {
    public:
        explicit Application(const ApplicationSpecification& specification);
        virtual ~Application();

        Application(const Application& other) = delete;
        Application(Application&& other) = delete;

        void PushLayer(Layer* layer);

        const ApplicationSpecification& GetSpecification() const { return m_Specification; }

        static Application& Get() { return *s_Instance; }

    protected:

        ApplicationSpecification m_Specification;

    private:
        void Run();

        static Application* s_Instance;

        LayerStack m_LayerStack;

        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication([[maybe_unused]] int argc, [[maybe_unused]] char** argv);
}
