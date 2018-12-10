#ifndef COREBASE_EXPORT_HELPER_HPP
#define COREBASE_EXPORT_HELPER_HPP

#if defined (_MSC_VER) || defined(__MINGW32)
#define CORE_LIBRARY_EXPORT __declspec(dllexport) 
#else
#define CORE_LIBRARY_EXPORT __attribute__((visibility("default")))
#endif

#endif // COREBASE_EXPORT_HELPER_HPP