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
	auto world = env->getObjectT<CubA4::world::World>(worldId);
	if (!world)
		return false;
	worldControl_->setCurrentWorld(world);
	game_.subscriptionHelper_.apply([world](CubA4::game::IGameSubscriber *subscriber)
	{
		subscriber->worldChanged(world);
	});
	return true;
}

CubA4::world::IWorldControl &GameControl::getWorldControl()
{
	return *worldControl_.get();
}