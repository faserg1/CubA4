#include "Game.hpp"
#include <game/IGameSubscriber.hpp>
using namespace CubA4::game;

Game::Game(CubA4::system::IAppCallback &appCallback) :
	appCallback_(appCallback), runGameLoop_(false), controller_(createController())
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

std::shared_ptr<controller::Controller> Game::createController()
{
	if (auto appClientCallback = dynamic_cast<CubA4::system::IAppClientCallback*>(&appCallback_))
		return std::make_shared<CubA4::game::controller::Controller>(*appClientCallback);
	return {};
}