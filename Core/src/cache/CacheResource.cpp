#include "./CacheResource.hpp"
using namespace CubA4::core::cache;
using namespace CubA4::core::filesystem;

CacheResource::CacheResource(boost::filesystem::path path) :
	File(path)
{
	
}

CacheResource::~CacheResource()
{
	
}

