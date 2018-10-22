#include "../../include/system/EnvironmentBuilder.hpp"
using namespace CubA4::core::system;

EnvironmentBuilder::EnvironmentBuilder(const EnvironmentBuilderData &data, const EnvironmentBuilderContext &context) :
	data_(data), context_(context)
{
	
}

EnvironmentBuilder::~EnvironmentBuilder()
{
	
}

const CubA4::render::IRenderInfo &EnvironmentBuilder::getRenderInfo() const
{
	return data_.renderInfo_;
}

std::shared_ptr<CubA4::render::engine::IRenderManager> EnvironmentBuilder::getRenderManager() const
{
	return data_.renderManager_;
}

void EnvironmentBuilder::registerBlock(std::shared_ptr<const CubA4::mod::object::IBlock> block)
{
	
}

void EnvironmentBuilder::registerWorld(std::shared_ptr<const CubA4::mod::world::IWorld> world)
{

}