#ifdef NEUCLID_SYSTEM_WINDOWS
	#define NOMINMAX
	#define WIN32_LEAN_AND_MEAN
	#include<windows.h>
	#include"neuclid_windows.h"
	#include"neuclid_windows_main.cpp"
#else
	#error unspecified or unsupported operating system
#endif
