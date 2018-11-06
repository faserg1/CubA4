#include "../../include/system/EnvironmentBuilder.hpp"
#include "../../include/world/World.hpp"
#include <IModInfo.hpp>
#include <object/IBlock.hpp>
#include <world/IWorldDefinition.hpp>
using namespace CubA4::core::system;

EnvironmentBuilder::EnvironmentBuilder(EnvironmentBuilderData &data, const EnvironmentBuilderContext &context) :
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

bool EnvironmentBuilder::registerBlock(std::shared_ptr<const CubA4::mod::object::IBlock> block)
{
	auto genId = data_.identityMap_.add(context_.modInfo_.getIdName(), block->getId());
	if (genId < 0)
		return false;
	data_.blocks_.insert(std::make_pair(genId, block));
	return true;
}

std::shared_ptr<const CubA4::mod::world::IWorld> EnvironmentBuilder::createWorld(std::shared_ptr<const CubA4::mod::world::IWorldDefinition> worldDef)
{
	auto genId = data_.identityMap_.add(context_.modInfo_.getIdName(), worldDef->getId());
	if (genId < 0)
		return {};
	auto world = std::make_shared<CubA4::world::World>(worldDef);
	data_.worlds_.insert(std::make_pair(genId, world));
	return world;
}