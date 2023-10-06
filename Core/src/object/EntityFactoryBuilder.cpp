#include <object/EntityFactoryBuilder.hpp>
#include <object/EntityBuilderData.hpp>
using namespace CubA4::object;

EntityFactoryBuilder::EntityFactoryBuilder(EntityBuilderData &data) :
	data_(data)
{

}

IEntityFactoryBuilder &EntityFactoryBuilder::applyPhysicsDefinition(const CubA4::physics::IPhysicsEntityDefinition &def)
{
	data_.physicsDefinition = &def;
	return *this;
}

IEntityFactoryBuilder &EntityFactoryBuilder::setEntityHandler(std::shared_ptr<IEntityHandler> handler)
{
	data_.handler = handler;
	return *this;
}

IEntityFactoryBuilder &EntityFactoryBuilder::attachCamera()
{
	data_.attachCamera = true;
	return *this;
}

IEntityFactoryBuilder &EntityFactoryBuilder::attachController(ControllerRules rules, ControllerFactory controllerSetup)
{
	data_.controllerRules = rules;
	data_.controllerFactory = controllerSetup;
	return *this;
}

IEntityFactoryBuilder &EntityFactoryBuilder::attachChunkAnchor(bool render)
{
	data_.chunkAnchor = true;
	data_.chunkRenderAnchor = render;
	return *this;
}