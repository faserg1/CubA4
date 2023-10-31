#pragma once

#include <functional>
#include <memory>
#include <object/TickTypes.hpp>
#include <base/Vector.hpp>
#include <object/EntityControllerTypes.hpp>
#include <game/controller/IContextActionsRules.hpp>

namespace CubA4::physics
{
	class IPhysicsEntityDefinition;
}

namespace CubA4::object
{
	class IEntityHandler;
	class IEntity;

	class IEntityFactoryBuilder
	{
	public:
		using ControllerFactory = std::function<void(EntityContextActions &)>;
		using ControllerRules = std::shared_ptr<CubA4::game::controller::IContextActionsRules>;

		virtual ~IEntityFactoryBuilder() = default;

		virtual IEntityFactoryBuilder &applyPhysicsDefinition(const CubA4::physics::IPhysicsEntityDefinition &def) = 0;
		virtual IEntityFactoryBuilder &setEntityHandler(std::shared_ptr<IEntityHandler> handler) = 0;
		virtual IEntityFactoryBuilder &attachCamera() = 0;
		virtual IEntityFactoryBuilder &attachController(ControllerRules rules, ControllerFactory controllerSetup) = 0;
		virtual IEntityFactoryBuilder &attachChunkAnchor(bool render) = 0;

		virtual IEntityFactoryBuilder &setupTick(TickTypes types) = 0;
	protected:
		explicit IEntityFactoryBuilder() = default;
	};
}
