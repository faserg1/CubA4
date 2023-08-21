#include <physics/PhysicsFactory.hpp>
#include <physics/BoxCollisionBodyDefinition.hpp>
using namespace CubA4::physics;

PhysicsFactory::PhysicsFactory() = default;

PhysicsFactory::~PhysicsFactory() = default;

std::shared_ptr<ICollistionBodyDefinition> PhysicsFactory::createBoxCollisionBody(const Vector3 &halfExtents, const Vector3 &offset)
{
	return std::make_shared<BoxCollisionBodyDefinition>(halfExtents, offset);
}
