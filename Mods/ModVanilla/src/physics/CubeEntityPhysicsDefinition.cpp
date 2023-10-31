#include <physics/CubeEntityPhysicsDefinition.hpp>
using namespace CubA4::physics;

CubeEntityPhysicsDefinition::CubeEntityPhysicsDefinition(std::shared_ptr<const ICollistionBodyDefinition> bodyDef) :
	bodyDef_(bodyDef)
{

}

CubeEntityPhysicsDefinition::~CubeEntityPhysicsDefinition() = default;

bool CubeEntityPhysicsDefinition::includePhysicsController() const
{
	return false;
}

float CubeEntityPhysicsDefinition::getMass() const
{
	return 1.f;
}

std::shared_ptr<const ICollistionBodyDefinition> CubeEntityPhysicsDefinition::getCollisonBody() const
{
	return bodyDef_;
}