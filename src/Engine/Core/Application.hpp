#pragma once

#ifdef CORE_GUI_BUILD
    #include "Platform/GUI/Core/GUIApplication.hpp"   
#else
    #include "Platform/Console/Core/ConsoleApplication.hpp"
#endif
