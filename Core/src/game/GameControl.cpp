#include <game/GameControl.hpp>
#include <core/Environment.hpp>
#include <game/IGameSubscriber.hpp>
#include <object/EntityFactory.hpp>

using namespace CubA4::game;

GameControl::GameControl(Core &core, CubA4::game::Game &game) :
	core_(core), game_(game), worldControl_(std::make_unique<world::WorldControl>(core))
{

}

bool GameControl::requestWorldChange(const std::string &worldId, const std::string &dimId)
{
	auto env = core_.getEnvironment();
	// If we can still exists in the same world, dimension should be changed
	if (dimId.empty())
		return false;
	std::shared_ptr<CubA4::world::World> world;
	if (worldId.empty())
		world = std::dynamic_pointer_cast<CubA4::world::World>(worldControl_->getCurrentWorld());
	else
		world = env->getObjectT<CubA4::world::World>(worldId);
	auto dim = env->getObjectT<CubA4::world::Dimension>(dimId);
	if (!world || !dim)
		return false;
	
	if (!worldControl_->setCurrentWorld(world) || !worldControl_->setCurrentDimension(dim))
		return false;

	game_.subscriptionHelper_.apply([world, dim](CubA4::game::IGameSubscriber *subscriber)
	{
		subscriber->worldChanged(world, dim);
	});
	return true;
}

CubA4::world::IWorldControl &GameControl::getWorldControl()
{
	return *worldControl_.get();
}

std::shared_ptr<CubA4::object::IEntity> GameControl::requestSpawn(std::shared_ptr<const CubA4::object::IEntityFactory> iFactory, IdType dimensionId,
	const CubA4::world::GlobalPosition &pos)
{
	auto dim = core_.getEnvironment()->getObjectT<CubA4::world::Dimension>(dimensionId);
	auto &world = dim->getWorld();
	auto worldId = core_.getEnvironment()->getId(&world);
	
	auto factory = std::dynamic_pointer_cast<const object::EntityFactory>(iFactory);
	auto entity = factory->create(worldId, dimensionId, pos);
	dim->addEntity(entity);
	return entity;
}