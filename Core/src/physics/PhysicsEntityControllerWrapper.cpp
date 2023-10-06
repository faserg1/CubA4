#include <physics/PhysicsEntityControllerWrapper.hpp>
#include <entt/entt.hpp>
#include <object/components/PhysicalBody.hpp>
using namespace CubA4::physics;

PhysicsEntityControllerWrapper::PhysicsEntityControllerWrapper(entt::registry &registry, entt::entity entity) :
	registry_(registry), entity_(entity)
{
	// TODO: assert that entity has physics
	// TODO: subscribe for destroy
}

void PhysicsEntityControllerWrapper::addVelocity(const CubA4::Vector3 &velocity)
{
	auto &physicalBody = registry_.get<CubA4::object::PhysicalBody>(entity_);
	physicalBody.collisionObject->setLinearVelocity(btVector3{velocity.x, velocity.y, velocity.z});
}