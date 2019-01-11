#include "./Directory.hpp"
using namespace CubA4::core::filesystem;

Directory::Directory(boost::filesystem::path path, bool createIfNotExists) :
	path_(path)
{
	if (createIfNotExists && !boost::filesystem::exists(path_))
		boost::filesystem::create_directories(path_);
}

Directory::~Directory()
{
	
}

bool Directory::exists(std::string path) const
{
	return boost::filesystem::exists(path_ / path);
}

bool Directory::isDirectory(std::string path) const
{
	return boost::filesystem::is_directory(path_ / path);
}

bool Directory::isFile(std::string path) const
{
	return !isDirectory(path);
}

std::vector<std::string> Directory::listDirectories() const
{
	return {};
}

std::vector<std::string> listFiles() const
{
	return {};
}
