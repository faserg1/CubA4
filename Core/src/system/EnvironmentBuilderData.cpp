#include "../../include/system/EnvironmentBuilderData.hpp"
using namespace CubA4::core::system;

EnvironmentBuilderData::EnvironmentBuilderData(
	std::shared_ptr<CubA4::render::engine::IRenderManager> renderManager,
	const CubA4::render::IRenderInfo &renderInfo)
	: renderInfo_(renderInfo), renderManager_(renderManager)
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

IdentityMap &EnvironmentBuilderData::getIdentityMap()
{
	return identityMap_;
}

std::map<int64_t, const std::shared_ptr<const CubA4::mod::object::IObject>> &EnvironmentBuilderData::getObjects()
{
	return objects_;
}