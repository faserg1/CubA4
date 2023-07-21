#pragma once

#if defined (_MSC_VER) || defined(__MINGW32)
#define CORE_LIBRARY_EXPORT __declspec(dllexport) 
#else
#define CORE_LIBRARY_EXPORT __attribute__((visibility("default")))
#endif
