#include <physics/DefaultBlockPhysicsDefinition.hpp>
using namespace CubA4::physics;

BlockShape DefaultBlockPhysicsDefinition::getShape(const CubA4::world::BlockData &data) const
{
	return BlockShape::Box;
}