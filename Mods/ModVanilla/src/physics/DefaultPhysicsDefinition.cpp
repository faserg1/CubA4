#include <physics/DefaultPhysicsDefinition.hpp>
using namespace CubA4::physics;
using namespace CubA4;

Vector3 DefaultPhysicsDefinition::getDefaultGravity() const
{
	return {0.f, -10.f, 0.f};
}