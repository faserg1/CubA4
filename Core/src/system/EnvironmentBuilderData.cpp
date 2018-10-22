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

