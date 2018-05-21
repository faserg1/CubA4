#include "../../include/config/FilePaths.hpp"

using namespace CubA4::core::config;

FilePaths::FilePaths(int argc, const char *const argv[])
{
	using namespace boost::filesystem;
	initialPath_ = current_path();
}

FilePaths::~FilePaths()
{
	
}

std::string FilePaths::configPath() const
{
	return (initialPath_ / "config").string();
}

std::string FilePaths::modsPath() const
{
	return (initialPath_ / "mods").string();
}

std::string FilePaths::renderPath() const
{
	return (initialPath_ / "render").string();
}

std::string FilePaths::logsPath() const
{
	return (initialPath_ / "logs").string();
}