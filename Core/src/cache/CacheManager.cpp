#include "./CacheManager.hpp"
#include "./Cache.hpp"
using namespace CubA4::core::cache;

CacheManager::CacheManager(boost::filesystem::path path) :
	path_(path)
{
	
}

CacheManager::~CacheManager()
{
	
}

std::shared_ptr<ICache> CacheManager::getResources(CacheType type, std::string moduleId)
{
	boost::filesystem::path p = path_;
	switch (type)
	{
		case CacheType::Core:
			p /= "core";
			break;
		case CacheType::Render:
			p /= "render";
			break;
		case CacheType::Mod:
			p /= "mod";
			break;
		case CacheType::Addon:
			p /= "addon";
			break;
	}
	p /= moduleId;
	return std::make_shared<Cache>(p, true);
}