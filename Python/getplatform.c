
#include "Python.h"

#ifndef PLATFORM
#define PLATFORM "unknown"
#endif

const char *
Py_GetPlatform(void)
{
    if (IsWindows()) {
        return "win32";
    } else if(IsLinux()) {
        return "linux2";
    }
	return PLATFORM;
}
