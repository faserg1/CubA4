#pragma once

#include <object/IEntityFactoryBuilder.hpp>

namespace CubA4::object
{
	struct EntityBuilderData;

	class EntityFactoryBuilder : public virtual IEntityFactoryBuilder
	{
	public:
		EntityFactoryBuilder(EntityBuilderData &data);

		IEntityFactoryBuilder &applyPhysicsDefinition(const CubA4::physics::IPhysicsEntityDefinition &def) override;
		IEntityFactoryBuilder &setEntityHandler(std::shared_ptr<IEntityHandler> handler) override;
		IEntityFactoryBuilder &attachCamera() override;
		IEntityFactoryBuilder &attachController(ControllerRules rules, ControllerFactory controllerSetup) override;
		IEntityFactoryBuilder &attachChunkAnchor(bool render) override;

		IEntityFactoryBuilder &setupTick(TickTypes types) override;
	private:
		EntityBuilderData &data_;
	};
}