#ifndef MOD_LOADER_LIBRARY_HPP
#define MOD_LOADER_LIBRARY_HPP

#ifndef LIBRARY_IMPORT_EXPORT_DECLARATIONS
#define LIBRARY_IMPORT_EXPORT_DECLARATIONS

#if defined (_MSC_VER) || defined(__MINGW32)
#define LIBRARY_EXPORT __declspec(dllexport) 
#define LIBRARY_IMPORT __declspec(dllimport)
#else
#define LIBRARY_EXPORT __attribute__((visibility("default")))
#define LIBRARY_IMPORT __attribute__((visibility("default")))
#endif

#endif // LIBRARY_IMPORT_EXPORT_DECLARATIONS

#ifdef MOD_LOADER_LIBRARY
#define MOD_LOADER_SHARED LIBRARY_EXPORT
#else // MOD_LOADER_LIBRARY
#define MOD_LOADER_SHARED LIBRARY_IMPORT
#endif // MOD_LOADER_LIBRARY

#endif // MOD_LOADER_LIBRARY_HPP