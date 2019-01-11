#include "./Resources.hpp"
#include "./Resource.hpp"
using namespace CubA4::core::resources;
using namespace CubA4::core::filesystem;

Resources::Resources(boost::filesystem::path path, bool createIfNotExists) :
	Directory(path, createIfNotExists), path_(path)
{
	
}

Resources::~Resources()
{
	
}

std::shared_ptr<IResource> Resources::get(std::string path) const
{
	return std::make_shared<Resource>(path_ / path);
}

std::shared_ptr<IResources> Resources::cd(std::string path) const
{
	return std::make_shared<Resources>(path_ / path);
}