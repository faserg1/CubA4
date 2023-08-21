#include <physics/BoxCollisionBodyDefinition.hpp>
using namespace CubA4::physics;
using namespace CubA4;

BoxCollisionBodyDefinition::BoxCollisionBodyDefinition(Vector3 halfExtents, Vector3 offset) :
	halfExtents_(halfExtents), offset_(offset)
{

}

BodyType BoxCollisionBodyDefinition::getType() const
{
	return BodyType::Box;
}

Vector3 BoxCollisionBodyDefinition::getHalfExtents() const
{
	return halfExtents_;
}

Vector3 BoxCollisionBodyDefinition::getOffset() const
{
	return offset_;
}