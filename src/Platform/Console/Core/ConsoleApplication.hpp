#pragma once
#include <string>

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

        Application(const ApplicationSpecification& specification);
        virtual ~Application() = default;

        Application(const Application& other) = delete;
        Application(Application&& other) = delete;

        const ApplicationSpecification& GetSpecification() { return m_Specification; }
        bool IsRunning() const { return m_Running; }

        static Application& Get() { return *s_Instance; }

        void Close();

    protected:

        ApplicationSpecification m_Specification;
        bool m_Running{ true };

    private:

        void Run();

        static Application* s_Instance;

        friend int ::main([[maybe_unused]] int argc, [[maybe_unused]] char** argv);
    };

    Application* CreateApplication([[maybe_unused]] int argc, [[maybe_unused]] char** argv);
}
