#include "./RenderGameHandler.hpp"
#include <game/IGame.hpp>
using namespace CubA4::render::engine;

RenderGameHandler::RenderGameHandler()
{
	
}

RenderGameHandler::~RenderGameHandler()
{
	
}

void RenderGameHandler::setGame(std::shared_ptr<const CubA4::core::game::IGame> game)
{
	gameSubscription_ = game->subscribe(this);
}

void RenderGameHandler::worldChanged(std::shared_ptr<const CubA4::mod::world::IWorld> newWorld)
{

}