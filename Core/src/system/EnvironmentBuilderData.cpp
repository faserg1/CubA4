#include "EnvironmentBuilderData.hpp"
using namespace CubA4::system;

EnvironmentBuilderData::EnvironmentBuilderData(const IAppClientCallback *appCallback, std::shared_ptr<CubA4::game::controller::IRootActions> actions)
	: appCallback_(appCallback), actions_(actions)
{
	
}

EnvironmentBuilderData::~EnvironmentBuilderData()
{
	
}

const CubA4::render::IRenderInfo &EnvironmentBuilderData::getRenderInfo() const
{
	if (!appCallback_)
		return *static_cast<CubA4::render::IRenderInfo*>(nullptr);
	return appCallback_->getRenderInfo();
}

std::shared_ptr<CubA4::render::engine::IRenderManager> EnvironmentBuilderData::getRenderManager() const
{
	if (!appCallback_)
		return {};
	return appCallback_->getRenderManager();
}

std::shared_ptr<CubA4::game::controller::IRootActions> EnvironmentBuilderData::getActions() const
{
	return actions_;
}

IdentityMap &EnvironmentBuilderData::getIdentityMap()
{
	return identityMap_;
}

std::unordered_map<int64_t, std::shared_ptr<CubA4::object::IObject>> &EnvironmentBuilderData::getObjects()
{
	return objects_;
}