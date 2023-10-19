#include "pch.hpp"
#include "InputDialog.hpp"

#include "Platform/GUI/Core/GUIApplication.hpp"

namespace AI {
#ifdef CORE_PLATFORM_WINDOWS
    #include <GLFW/glfw3.h>
    #define GLFW_EXPOSE_NATIVE_WIN32
    #include <GLFW/glfw3native.h>

    std::string InputDialog::OpenFileDialog(const char *filter) {
        OPENFILENAMEA ofn;
        CHAR szFile[260] = { 0 };
        CHAR currentDir[256] = { 0 };
        ZeroMemory(&ofn, sizeof(OPENFILENAME));
        ofn.lStructSize = sizeof(OPENFILENAME);
        ofn.hwndOwner = glfwGetWin32Window(Core::Application::Get().GetWindow().GetNativeWindow());
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        if (GetCurrentDirectoryA(256, currentDir))
            ofn.lpstrInitialDir = currentDir;
        ofn.lpstrFilter = filter;
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

        if (GetOpenFileNameA(&ofn) == TRUE)
            return ofn.lpstrFile;

        return std::string();
    }
#elif CORE_PLATFORM_LINUX
#error "TODO: Implement InputDialog::OpenFileDialog() for Linux!"
    std::string InputDialog::OpenFileDialog(const char *filter) {
               return std::string();
    }
#endif
}
