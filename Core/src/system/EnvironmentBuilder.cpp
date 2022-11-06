#include "EnvironmentBuilder.hpp"
#include "../world/World.hpp"
#include <IModInfo.hpp>
#include <object/IObject.hpp>
#include <world/IWorldDefinition.hpp>
using namespace CubA4::system;

EnvironmentBuilder::EnvironmentBuilder(EnvironmentBuilderData &data, const EnvironmentBuilderContext &context) :
	data_(data), context_(context)
{
	
}

EnvironmentBuilder::~EnvironmentBuilder()
{
	
}

const CubA4::render::IRenderInfo &EnvironmentBuilder::getRenderInfo() const
{
	return data_.getRenderInfo();
}

std::shared_ptr<CubA4::render::engine::IRenderManager> EnvironmentBuilder::getRenderManager() const
{
	return data_.getRenderManager();
}

bool EnvironmentBuilder::registerObject(std::shared_ptr<const CubA4::object::IObject> object)
{
	auto genId = data_.getIdentityMap().add(context_.modInfo_.getIdName(), object->getId());
	if (genId < 0)
		return false;
	data_.getObjects().insert(std::make_pair(genId, object));
	return true;
}

std::shared_ptr<const CubA4::world::IWorld> EnvironmentBuilder::createWorld(std::shared_ptr<const CubA4::world::IWorldDefinition> worldDef)
{
	auto genId = data_.getIdentityMap().add(context_.modInfo_.getIdName(), worldDef->getId());
	if (genId < 0)
		return {};
	auto world = std::make_shared<CubA4::world::World>(worldDef);
	data_.getObjects().insert(std::make_pair(genId, world));
	return world;
}