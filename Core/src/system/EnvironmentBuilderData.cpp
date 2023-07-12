#include "EnvironmentBuilderData.hpp"
using namespace CubA4::system;

EnvironmentBuilderData::EnvironmentBuilderData(
	std::shared_ptr<CubA4::render::engine::IRenderManager> renderManager,
	const CubA4::render::IRenderInfo &renderInfo, std::shared_ptr<CubA4::game::controller::IRootActions> actions)
	: renderInfo_(renderInfo), renderManager_(renderManager), actions_(actions)
{
	
}

EnvironmentBuilderData::~EnvironmentBuilderData()
{
	
}

const CubA4::render::IRenderInfo &EnvironmentBuilderData::getRenderInfo() const
{
	return renderInfo_;
}

std::shared_ptr<CubA4::render::engine::IRenderManager> EnvironmentBuilderData::getRenderManager() const
{
	return renderManager_;
}

std::shared_ptr<CubA4::game::controller::IRootActions> EnvironmentBuilderData::getActions() const
{
	return actions_;
}

IdentityMap &EnvironmentBuilderData::getIdentityMap()
{
	return identityMap_;
}

std::map<int64_t, const std::shared_ptr<const CubA4::object::IObject>> &EnvironmentBuilderData::getObjects()
{
	return objects_;
}