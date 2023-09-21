#ifdef NEUCLID_SYSTEM_WINDOWS
	#define NOMINMAX
	#define WIN32_LEAN_AND_MEAN
	#include<windows.h>

	#define GLEW_STATIC
	#include"3rd_party/glew-2.2.0/include/GL/glew.h"
	#include"3rd_party/glew-2.2.0/include/GL/wglew.h"

	#include"neuclid_windows.h"
	#include"neuclid_windows_main.cpp"
#else
	#error unspecified or unsupported operating system
#endif
