#include <controller/PlayerController.hpp>
#include <object/IEntity.hpp>
#include <object/components/CameraComponent.hpp>
using namespace CubA4::object;

void PlayerController::onAction(const std::string &action, EntityArg entity)
{

}

void PlayerController::onActionAxis(const std::string &action, int32_t x, int32_t y, EntityArg entity)
{
	auto player = entity.lock();
	if (!player)
		return;
	if (auto *cameraComponent = player->getCameraComponent(); cameraComponent && cameraComponent->camera)
	{
		// TODO: read value from settings?
		float sensivity = 0.05f;
		cameraComponent->camera->rotate(0, -y * sensivity, x * sensivity);
	}
}

void PlayerController::onActionPosition(const std::string &action, int32_t x, int32_t y, EntityArg entity)
{

}

void PlayerController::onActionPositionMove(const std::string &action, int32_t x, int32_t y, EntityArg entity)
{

}