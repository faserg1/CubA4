#include <controller/PlayerController.hpp>
#include <object/IEntity.hpp>
#include <object/components/CameraComponent.hpp>
#include <physics/IPhysicsEntityControllerWrapper.hpp>
#include <ICore.hpp>
#include <game/IGame.hpp>
#include <game/IGameControl.hpp>
#include <world/IDimension.hpp>
#include <world/IWorldControl.hpp>
#include <ModControl.hpp>
#include <engine/IRenderManager.hpp>
#include <engine/debug/IRenderDebug.hpp>
#include <engine/debug/IRenderDebugCollection.hpp>
using namespace CubA4::object;

PlayerController::PlayerController(std::shared_ptr<const CubA4::ICore> core, std::shared_ptr<const CubA4::mod::ModControl> modControl) :
	core_(core), modControl_(modControl)
{

}

void PlayerController::onAction(const std::string &action, EntityArg entity)
{
	auto player = entity.lock();
	if (!player)
		return;
	checkMovements(action, player);
	checkMain(action, player);
}

void PlayerController::onActionAxis(const std::string &action, int32_t x, int32_t y, EntityArg entity)
{
	auto player = entity.lock();
	if (!player)
		return;
	if (action != "camera")
		return;
	if (auto *cameraComponent = player->getCameraComponent(); cameraComponent && cameraComponent->camera)
	{
		// TODO: read value from settings?
		float sensivity = 0.05f;
		cameraComponent->camera->rotate(0, -y * sensivity, x * sensivity);

		using namespace CubA4::world;
		auto dim = core_->getGame()->getEntityManager()->getCurrentDimension(*player);
		auto ray = cameraComponent->camera->getRay();
		auto fPos = ray.position.inBlockPos() + ray.position.blockPosition();
		auto fPosTo = ray.direction * ChunkSize + fPos;
		auto result = dim->closestBlockRayTest(ray.position, GlobalPosition(fPosTo));

		if (!debugBlock_)
		{
			auto renderManager = core_->getRenderManager();
			debugBlock_ = renderManager->getDebug()->addCollection();
		}
		debugBlock_->clear();
		debugBlock_->addCube(result.chunkPos, convertPos<float>(result.blockPos));
	}
}

void PlayerController::onActionPosition(const std::string &action, int32_t x, int32_t y, EntityArg entity)
{

}

void PlayerController::onActionPositionMove(const std::string &action, int32_t x, int32_t y, EntityArg entity)
{

}

void PlayerController::checkMovements(const std::string &action, std::shared_ptr<IEntity> player)
{
	auto controller = player->getPhysicsController();
	if (!controller)
		return;
	if (action == "up")
	{
		controller->applyImpulse({0, 4, 0}, {0, 0, 0});
	}
}

void PlayerController::checkMain(const std::string &action, std::shared_ptr<IEntity> player)
{
	if (action == "click")
	{
		if (auto *cameraComponent = player->getCameraComponent(); cameraComponent && cameraComponent->camera)
		{
			using namespace CubA4::world;
			auto dim = core_->getGame()->getEntityManager()->getCurrentDimension(*player);
			auto ray = cameraComponent->camera->getRay();
			auto fPos = ray.position.inBlockPos() + ray.position.blockPosition();
			auto fPosTo = ray.direction * ChunkSize + fPos;
			auto result = dim->closestBlockRayTest(ray.position, GlobalPosition(fPosTo));

			ChunkBModification::RemoveInfo removeBlock
			{
				.pos = result.blockPos,
				.layer = 0
			};

			ChunkBModification::AddInfo addBlock
			{
				.blockId = 0, // pass the id
				.pos = result.blockPos + BlockInChunkPos{1, 0, 0}
			};

			ChunkBModification modification(result.chunkPos);

			//modification.add = {addBlock};
			modification.remove = {removeBlock};

			std::vector<ChunkBModification> modifications
			{
				modification
			};

			modControl_->getGameControl()->getWorldControl().requestChanges(modifications, dim->getId());
		}
	}
}