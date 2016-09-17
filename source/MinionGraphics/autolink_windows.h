#ifndef AUTOLINK_WINDOWS_H
#define AUTOLINK_WINDOWS_H

#if defined(_WIN32) || defined(WIN32)

#pragma comment(lib, "opengl32.lib")

#if defined(DEBUG) || defined (_DEBUG)
//#pragma comment(lib, "glew32sd.lib")
//#pragma comment(lib, "glfw3d.lib")
#pragma comment(lib, "glew32_x86_Debug_VS2015.lib")
#pragma comment(lib, "glfw3_x86_Debug_VS2015.lib")
#pragma comment(lib, "Utilitiesx86Debug.lib")
#else
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#endif

#endif

#endif // !AUTOLINK_WINDOWS
