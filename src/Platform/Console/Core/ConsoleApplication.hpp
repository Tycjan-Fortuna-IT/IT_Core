#pragma once
#include <string>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv);

namespace Core {
    class Application {
    public:

        Application(const std::string& name = "Core Application");
        virtual ~Application() = default;



    private:

        void Run();

        static Application* s_Instance;

        std::string m_Name;

        friend int ::main([[maybe_unused]] int argc, [[maybe_unused]] char** argv);
    };

    Application* CreateApplication();
}
