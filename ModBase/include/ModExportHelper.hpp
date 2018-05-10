#ifndef EXPORT_HELPER_HPP
#define EXPORT_HELPER_HPP

#if defined (_MSC_VER) || defined(__MINGW32)
#define MOD_LIBRARY_EXPORT __declspec(dllexport) 
#else
#define MOD_LIBRARY_EXPORT __attribute__((visibility("default")))
#endif

#endif // EXPORT_HELPER_HPP