#include "../../include/system/EnvironmentBuilder.hpp"
using namespace CubA4::core::system;

EnvironmentBuilder::EnvironmentBuilder(std::shared_ptr<CubA4::render::engine::IRenderManager> renderManager,
	const CubA4::render::IRenderInfo &renderInfo) :
	renderInfo_(renderInfo), renderManager_(renderManager)
{
	
}

EnvironmentBuilder::~EnvironmentBuilder()
{
	
}

const CubA4::render::IRenderInfo &EnvironmentBuilder::getRenderInfo() const
{
	return renderInfo_;
}

std::shared_ptr<CubA4::render::engine::IRenderManager> EnvironmentBuilder::getRenderManager() const
{
	return renderManager_;
}

void EnvironmentBuilder::registerModel(std::shared_ptr<const CubA4::core::model::IModel> model)
{

}

void EnvironmentBuilder::registerWorld(std::shared_ptr<const CubA4::mod::world::IWorld> world)
{

}