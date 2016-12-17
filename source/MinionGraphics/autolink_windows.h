#ifndef AUTOLINK_WINDOWS_H
#define AUTOLINK_WINDOWS_H

#if defined(_WIN32) || defined(WIN32)

#pragma comment(lib, "opengl32.lib")

#if _MSC_VER == 1900
	#define VS_VERSION "VS2015"
#elif _MSC_VER == 1800
	#define VS_VERSION "VS2013"
#endif

#if defined(DEBUG) || defined (_DEBUG)
	#if defined _M_X64 
		#pragma comment(lib, "glew32_x64_Debug_" VS_VERSION ".lib")
		#pragma comment(lib, "glfw3_x64_Debug_" VS_VERSION ".lib")
		#pragma comment(lib, "Utilitiesx64Debug.lib")
	#else
		#pragma comment(lib, "glew32_x86_Debug_" VS_VERSION ".lib")
		#pragma comment(lib, "glfw3_x86_Debug_" VS_VERSION ".lib")
		#pragma comment(lib, "Utilitiesx86Debug.lib")
	#endif
#else
	#if defined _M_X64 
		#pragma comment(lib, "glew32_x64_Release_" VS_VERSION ".lib")
		#pragma comment(lib, "glfw3_x64_Release_" VS_VERSION ".lib")
		#pragma comment(lib, "Utilitiesx64Release.lib")
	#else
		#pragma comment(lib, "glew32_x86_Release_" VS_VERSION ".lib")
		#pragma comment(lib, "glfw3_x86_Release_" VS_VERSION ".lib")
		#pragma comment(lib, "Utilitiesx86Debug.lib")
	#endif
#endif

#endif

#endif // !AUTOLINK_WINDOWS
