#ifndef MINION_GRAPHICS_PRE_PROCESS_H
#define MINION_GRAPHICS_PRE_PROCESS_H

#if (defined(_WIN32) || defined(_WIN64)) && defined(MINION_GRAPHICS_SHARED)
#   define MINION_GRAPHICS_CALL          __stdcall
#   define MINION_GRAPHICS_CDECL_CALL    __cdecl
#   define MINION_GRAPHICS_EXPORT_API    __declspec(dllexport)
#   define MINION_GRAPHICS_IMPORT_API    __declspec(dllimport)
#else
#   define MINION_GRAPHICS_CALL
#   define MINION_GRAPHICS_CDECL_CALL
#   define MINION_GRAPHICS_EXPORT_API
#   define MINION_GRAPHICS_IMPORT_API
#endif

#if defined MINION_GRAPHICS_SHARED_EXPORT
#   define MINION_GRAPHICS_API MINION_EXPORT_API
#elif defined MINION_GRAPHICS_SHARED
#   define MINION_GRAPHICS_API MINION_IMPORT_API
#   if defined(_MSC_VER) && !defined(MINION_GRAPHICS_NO_AUTO_LIB)
#       ifdef _WIN64
#           if defined (_DEBUG)
#				pragma comment(lib, "MinionGraphics_x64_d")
#			else
#				pragma comment(lib, "MinionGraphics_x64")
#			endif
#       else
#			if defined (_DEBUG)
#				pragma comment(lib, "MinionGraphics_x86_d")
#			else
#				pragma comment(lib, "MinionGraphics_x86")
#			endif
#       endif
#   endif
#else
#   define MINION_GRAPHICS_API
#   if defined(_MSC_VER) && !defined(MINION_GRAPHICS_NO_AUTO_LIB)
#       ifdef _WIN64
#           if defined (_DEBUG)
#				pragma comment(lib, "libMinionGraphics_x64_d")
#			else
#				pragma comment(lib, "libMinionGraphics_x64")
#			endif
#       else
#			if defined (_DEBUG)
#				pragma comment(lib, "libMinionGraphics_x86_d")
#			else
#				pragma comment(lib, "libMinionGraphics_x86")
#			endif
#       endif
#   endif
#endif

#endif // !MINION_PRE_PROCESS
