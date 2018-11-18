#include "../../include/game/Game.hpp"
using namespace CubA4::core::game;

Game::Game() :
	runGameLoop_(false)
{
	
}

Game::~Game()
{
	
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

void Game::setupEnvironment(std::shared_ptr<CubA4::core::system::Environment> env)
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