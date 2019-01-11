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
	std::vector<std::string> dirs;
	for (auto entry = boost::filesystem::directory_iterator(path_); entry != boost::filesystem::directory_iterator(); entry++)
	{
		auto path = entry->path();
		if (boost::filesystem::is_directory(path))
			dirs.push_back(path.filename());
	}
	return std::move(dirs);
}

std::vector<std::string> Directory::listFiles() const
{
	std::vector<std::string> files;
	for (auto entry = boost::filesystem::directory_iterator(path_); entry != boost::filesystem::directory_iterator(); entry++)
	{
		auto path = entry->path();
		if (!boost::filesystem::is_directory(path))
			files.push_back(path.filename());
	}
	return std::move(files);
}
