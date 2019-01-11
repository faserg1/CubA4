#include "./ResourcesManager.hpp"
#include "./Resources.hpp>
using namespace CubA4::core::resources;

ResourcesManager::ResourcesManager(boost::filesystem::path path) :
	path_(path)
{
	
}

ResourcesManager::~ResourcesManager()
{
	
}

std::shared_ptr<IResources> ResourcesManager::getResources(ResourcesType type, std::string moduleId)
{
	boost::filesystem::path p = path_;
	switch (type)
	{
		case ResourcesType::Mod:
			p /= "mod";
			break;
		case ResourcesManager::Addon:
			p /= "addon";
			break;
	}
	p /= moduleId;
	return std::make_shared<Resources>(p, true);
}