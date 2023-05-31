#include "./RenderGameHandler.hpp"
#include <game/IGame.hpp>
#include <world/IWorld.hpp>
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::pipeline;

RenderGameHandler::RenderGameHandler(std::shared_ptr<IRenderEngineWorldPipeline> updater) :
	updater_(updater)
{
}

RenderGameHandler::~RenderGameHandler()
{
	
}

void RenderGameHandler::setGame(std::shared_ptr<const CubA4::game::IGame> game)
{
	if (!game) // Game destroing
	{
		// TODO: Подумать над RAII, но учитывать, что здесь могут находится ресурсы модов
		currentWorld_.reset();
		worldSubscription_.reset();
		gameSubscription_.reset();
		return;
	}
	gameSubscription_ = game->subscribe(this);
}


void RenderGameHandler::worldChanged(std::shared_ptr<const CubA4::world::IWorld> newWorld)
{
	currentWorld_ = newWorld;
	worldSubscription_ = currentWorld_->subscribe(this);
	recompileWorld();
}

void RenderGameHandler::recompileWorld()
{
	auto chunks = currentWorld_->getChunks();
	updater_->pushChunks(std::move(chunks));
}