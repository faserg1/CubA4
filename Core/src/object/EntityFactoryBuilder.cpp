#include <object/EntityFactoryBuilder.hpp>
#include <object/EntityBuilderData.hpp>
using namespace CubA4::object;

EntityFactoryBuilder::EntityFactoryBuilder(EntityBuilderData &data) :
	data_(data)
{

}

void EntityFactoryBuilder::applyPhysicsDefinition(const CubA4::physics::IPhysicsEntityDefinition &def)
{
	data_.physicsDefinition = &def;
}