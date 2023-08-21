#include <physics/PlayerPhysicsDefinition.hpp>
using namespace CubA4::physics;

PlayerPhysicsDefinition::PlayerPhysicsDefinition(std::shared_ptr<const ICollistionBodyDefinition> bodyDef) :
	bodyDef_(bodyDef)
{

}

PlayerPhysicsDefinition::~PlayerPhysicsDefinition() = default;

float PlayerPhysicsDefinition::getMass() const
{
	return 1.f;
}

std::shared_ptr<const ICollistionBodyDefinition> PlayerPhysicsDefinition::getCollisonBody() const
{
	return bodyDef_;
}