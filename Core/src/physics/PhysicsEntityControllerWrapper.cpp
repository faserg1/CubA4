#include <physics/PhysicsEntityControllerWrapper.hpp>
#include <entt/entt.hpp>
#include <object/components/PhysicalBody.hpp>
using namespace CubA4::physics;

PhysicsEntityControllerWrapper::PhysicsEntityControllerWrapper(entt::registry &registry, entt::entity entity) :
	registry_(registry), entity_(entity)
{
	if (!registry_.all_of<CubA4::object::PhysicalBody>(entity_))
	{
		// TODO: assert
		return;
	}

}

void PhysicsEntityControllerWrapper::setVelocity(const CubA4::Vector3 &velocity)
{
	auto &physicalBody = registry_.get<CubA4::object::PhysicalBody>(entity_);
	physicalBody.collisionObject->setLinearVelocity(btVector3{velocity.x, velocity.y, velocity.z});
	physicalBody.collisionObject->activate();
}

void PhysicsEntityControllerWrapper::applyImpulse(const CubA4::Vector3 &velocity, const CubA4::Vector3 &relativePosition)
{
	auto &physicalBody = registry_.get<CubA4::object::PhysicalBody>(entity_);
	auto vel = btVector3{velocity.x, velocity.y, velocity.z};
	auto relPos = btVector3{relativePosition.x, relativePosition.y, relativePosition.z};
	physicalBody.collisionObject->applyImpulse(vel, relPos);
	physicalBody.collisionObject->activate();
}