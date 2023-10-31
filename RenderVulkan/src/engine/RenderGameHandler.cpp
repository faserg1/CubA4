#include "./RenderGameHandler.hpp"
#include <game/IGame.hpp>
#include <world/IWorld.hpp>
#include <ICore.hpp>
#include <core/IEnvironment.hpp>
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::pipeline;
using namespace CubA4::object;

RenderGameHandler::RenderGameHandler(std::shared_ptr<const CubA4::ICore> core,
	std::shared_ptr<IRenderEngineWorldPipeline> worldUpdater, std::shared_ptr<IRenderEngineEntityPipeline> entityUpdater) :
	core_(core), worldUpdater_(worldUpdater), entityUpdater_(entityUpdater)
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
		dimensionSubscription_.reset();
		gameSubscription_.reset();
		entitySubscription_.reset();

		currentWorldId_ = std::numeric_limits<IdType>::max();
		currentDimensionId_ = std::numeric_limits<IdType>::max();

		return;
	}
	gameSubscription_ = game->subscribe(this);
	entitySubscription_ = game->getEntityRenderManager()->subscribe(this);
}


void RenderGameHandler::worldChanged(std::shared_ptr<const CubA4::world::IWorld> newWorld,
	std::shared_ptr<const CubA4::world::IDimension> newDimension)
{
	auto env = core_->getEnvironment();

	currentWorld_ = newWorld;
	currentDimension_ = newDimension;
	worldSubscription_ = currentWorld_->subscribe(this);
	dimensionSubscription_ = currentDimension_->subscribe(this);

	currentWorldId_ = env->getId(currentWorld_);
	currentDimensionId_ = env->getId(currentDimension_);

	recompileWorld();
}

void RenderGameHandler::onActiveChunksUpdated()
{
	recompileWorld();
}

void RenderGameHandler::onLoadedChunksUpdated()
{
	recompileWorld();
}

void RenderGameHandler::onChunkUpdated(const CubA4::world::ChunkPos &chunkPos)
{
	auto chunk = currentDimension_->findChunk(chunkPos);
	worldUpdater_->pushChunks({chunk});
}

void RenderGameHandler::onEntityAdded(Transform &tr, WorldInfo &wi, RenderInfoComponent &render)
{
	if (wi.worldId != currentWorldId_ || wi.dimensionId != currentDimensionId_)
		return;
	entityUpdater_->onEntityAdded(tr, wi, render);
}

void RenderGameHandler::onEntityUpdated(Transform &tr, WorldInfo &wi, RenderInfoComponent &render)
{
	if (wi.worldId != currentWorldId_ || wi.dimensionId != currentDimensionId_)
		return;
	entityUpdater_->onEntityUpdated(tr, wi, render);
}

void RenderGameHandler::onEntityRemoved(Transform &tr, WorldInfo &wi, RenderInfoComponent &render)
{
	if (wi.worldId != currentWorldId_ || wi.dimensionId != currentDimensionId_)
		return;
	entityUpdater_->onEntityRemoved(tr, wi, render);
}

void RenderGameHandler::recompileWorld()
{
	// TODO: recompile only needed
	auto chunks = currentDimension_->getChunks();
	worldUpdater_->pushChunks(std::move(chunks));
}