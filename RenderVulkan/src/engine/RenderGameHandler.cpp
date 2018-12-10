#include "./RenderGameHandler.hpp"
#include <game/IGame.hpp>
#include <world/IWorld.hpp>
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::pipeline;

RenderGameHandler::RenderGameHandler(std::shared_ptr<IRenderEnginePipelineUpdater> updater) :
	updater_(updater)
{
	
}

RenderGameHandler::~RenderGameHandler()
{
	
}

void RenderGameHandler::setGame(std::shared_ptr<const CubA4::core::game::IGame> game)
{
	if (!game) // Game destroing
		return;
	gameSubscription_ = game->subscribe(this);
}

void RenderGameHandler::worldChanged(std::shared_ptr<const CubA4::mod::world::IWorld> newWorld)
{
	currentWorld_ = newWorld;
	worldSubscription_ = currentWorld_->subscribe(this);
	recompileWorld();
}

void RenderGameHandler::recompileWorld()
{
	
}