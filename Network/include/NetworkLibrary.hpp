#pragma once

#ifndef NETWORK_NETWORK_EXPORT_DECLARATIONS
#define NETWORK_NETWORK_EXPORT_DECLARATIONS

#if defined (_MSC_VER) || defined(__MINGW32)
#define LIBRARY_EXPORT __declspec(dllexport) 
#define LIBRARY_IMPORT __declspec(dllimport)
#else
#define LIBRARY_EXPORT __attribute__((visibility("default")))
#define LIBRARY_IMPORT __attribute__((visibility("default")))
#endif

#endif // NETWORK_NETWORK_EXPORT_DECLARATIONS

#ifdef NETWORK_LIBRARY
#define LIBRARY_SHARED LIBRARY_EXPORT
#else // NETWORK_LIBRARY
#define LIBRARY_SHARED LIBRARY_IMPORT
#endif // NETWORK_NETWORK_LIBRARY
