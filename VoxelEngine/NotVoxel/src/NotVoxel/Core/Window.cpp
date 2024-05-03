#include "pch.h"
#include "Window.h"

#ifdef VOXEL_PLATFORM_WINDOWS
	#include "Platform/OperatingSystem/Windows/WinWindow.h"
#endif

namespace Forge
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef VOXEL_PLATFORM_WINDOWS
		return CreateScope<WinWindow>(props);
#else
		CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}