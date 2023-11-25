#include "pch.hpp"
#include "InputDialog.hpp"

#include "Engine/Core/PlatformDetection.hpp"

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
#elif defined(CORE_PLATFORM_LINUX)
    #include <gtk/gtk.h>

    std::string InputDialog::OpenFileDialog([[maybe_unused]] const char* filter)
	{
		GtkWidget* dialog;
		int res;

		if (!gtk_init_check(NULL, NULL) )
		{
			return "";
		}

		dialog = gtk_file_chooser_dialog_new("Open File", nullptr, GTK_FILE_CHOOSER_ACTION_OPEN, "_Cancel", GTK_RESPONSE_CANCEL, "_Open", GTK_RESPONSE_ACCEPT, nullptr);

		res = gtk_dialog_run(GTK_DIALOG(dialog));
		std::string ret;
		if (res == GTK_RESPONSE_ACCEPT)
		{
			char* filename;
			GtkFileChooser* chooser = GTK_FILE_CHOOSER(dialog);
			filename = gtk_file_chooser_get_filename(chooser);
			ret = filename;
			g_free(filename);
		}

		gtk_widget_destroy(dialog);
		return ret;
	}
#endif
}
