#include "Game.hpp"
#include <world/IWorld.hpp>
#include <object/IBlock.hpp>
#include "../system/Environment.hpp"
#include <game/IGameSubscriber.hpp>
using namespace CubA4::game;

Game::Game() :
	runGameLoop_(false)
{
	
}

Game::~Game()
{
	
}

std::unique_ptr<CubA4::util::ISubscription> Game::subscribe(IGameSubscriber *subscriber) const
{
	return std::move(subscriptionHelper_.add(subscriber));
}

void Game::run()
{
	runGameLoop_ = true;
	gameThread_ = std::thread(&Game::loop, this);
}

void Game::stop()
{
	runGameLoop_ = false;
	gameThread_.join();
}

void Game::setupEnvironment(std::shared_ptr<CubA4::system::Environment> env)
{
	env_ = env;
}

void Game::loop()
{
	// TODO: [OOKMAI] Убрать к чертовой бабушке и написать по нормальному
	// Temporary
	auto world = env_->getObjectT<CubA4::world::IWorld>("#vanilla@testWorld");
	subscriptionHelper_.apply([world](CubA4::game::IGameSubscriber *subscriber)
	{
		subscriber->worldChanged(world);
	});
	while (runGameLoop_)
	{
		std::this_thread::yield();
	}
}