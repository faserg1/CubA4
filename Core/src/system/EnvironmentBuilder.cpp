#include "EnvironmentBuilder.hpp"
#include <IModInfo.hpp>
#include <object/IObject.hpp>
#include <world/IWorldDefinition.hpp>
#include <world/World.hpp>
#include <world/Dimension.hpp>
using namespace CubA4::system;

EnvironmentBuilder::EnvironmentBuilder(Core &core, EnvironmentBuilderData &data, const EnvironmentBuilderContext &context) :
	core_(core), data_(data), context_(context)
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

std::shared_ptr<CubA4::game::controller::IRootActions> EnvironmentBuilder::getActions() const
{
	return data_.getActions();
}

bool EnvironmentBuilder::registerObject(std::shared_ptr<CubA4::object::IObject> object)
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
	auto world = std::make_shared<CubA4::world::World>(core_, worldDef);
	data_.getObjects().insert(std::make_pair(genId, world));
	for (auto dimDescription : worldDef->getDimensionDescriptions())
	{
		auto genId = data_.getIdentityMap().add(context_.modInfo_.getIdName(), worldDef->getId(), dimDescription.get().getId());
		if (genId < 0)
			continue;
		auto dim = std::make_shared<CubA4::world::Dimension>(core_, dimDescription.get());
		world->addDimension(dim);
		data_.getObjects().insert(std::make_pair(genId, dim));
	}
	return world;
}

