#pragma once
#include "Debug/Logger.hpp"
#include "Engine/Core/Application.hpp"

extern Core::Application* Core::CreateApplication();

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    Core::Logger::Init();

    Core::Application* application = Core::CreateApplication();

    application->Run();

    delete application;
}
