#include <game/GameControl.hpp>
#include <system/Environment.hpp>
#include <game/IGameSubscriber.hpp>

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