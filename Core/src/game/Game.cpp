#include "Game.hpp"
#include <game/IGameSubscriber.hpp>
using namespace CubA4::game;

Game::Game(CubA4::system::IAppCallback &appCallback) :
	appCallback_(appCallback), runGameLoop_(false), controller_(std::make_shared<CubA4::game::controller::Controller>(appCallback))
{
	
}

Game::~Game()
{
	
}

std::unique_ptr<CubA4::util::ISubscription> Game::subscribe(IGameSubscriber *subscriber) const
{
	return std::move(subscriptionHelper_.add(subscriber));
}

std::shared_ptr<const CubA4::game::controller::IController> Game::getController() const
{
	return controller_;
}

std::shared_ptr<CubA4::game::controller::IController> Game::getController()
{
	return controller_;
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
	while (runGameLoop_)
	{
		std::this_thread::yield();
	}
}