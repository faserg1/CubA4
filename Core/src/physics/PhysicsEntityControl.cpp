#include <physics/PhysicsEntityControl.hpp>
#include <physics/PhysicsEntityControllerWrapper.hpp>
#include <object/Entity.hpp>
using namespace CubA4::physics;

std::shared_ptr<IPhysicsEntityControllerWrapper> PhysicsEntityControl::createController(const CubA4::object::IEntity &entityIface)
{
	auto &entity = *dynamic_cast<const CubA4::object::Entity*>(&entityIface);
	// TODO: check for physics
	return std::make_shared<PhysicsEntityControllerWrapper>(entity.getRegistry(), entity.getEntity());
}