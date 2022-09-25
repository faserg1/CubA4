#include "./Runtime.hpp"
#ifdef __linux__
#include <cstdlib>
#elif _WIN32
#include <windows.h>
#endif



using namespace CubA4::core::system;

Runtime::Runtime()
{
	
}

Runtime::~Runtime()
{
	
}

void Runtime::addModuleSearchPath(const std::string &path)
{
	#ifdef __linux__
	using namespace std::string_literals;
	const auto p1 = std::string(getenv("PATH"));
	const auto newPathSearch = "PATH="s + p1 + ";"s + path;
	putenv(newPathSearch.c_str());
	#elif _WIN32
	SetDllDirectoryA(path.c_str());
	#endif
}