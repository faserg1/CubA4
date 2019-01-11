#include "./Cache.hpp"
#include "./CacheResource.hpp"
using namespace CubA4::core::cache;
using namespace CubA4::core::filesystem;

Cache::Cache(boost::filesystem::path path, bool createIfNotExists) :
	Directory(path, createIfNotExists), path_(path)
{
	
}

Cache::~Cache()
{
	
}

std::shared_ptr<ICacheResource> Cache::get(std::string path) const
{
	return std::make_shared<CacheResource>(path_ / path);
}

std::shared_ptr<ICache> Cache::cd(std::string path, bool createIfNotExists) const
{
	return std::make_shared<Cache>(path_ / path, createIfNotExists);
}