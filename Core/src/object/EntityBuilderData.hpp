#pragma once

#include <memory>
#include <vector>
#include <object/EntityControllerTypes.hpp>
#include <object/TickTypes.hpp>

namespace CubA4::render::engine::model
{
	class IRenderModel;
}

namespace CubA4::physics
{
	class IPhysicsEntityDefinition; 
}

namespace CubA4::object
{
	class IEntityHandler;

	struct EntityBuilderData
	{
		using ControllerFactory = std::function<void(EntityContextActions &)>;
		
		std::shared_ptr<const CubA4::render::engine::model::IRenderModel> renderModel;
		const CubA4::physics::IPhysicsEntityDefinition *physicsDefinition = nullptr;
		std::shared_ptr<IEntityHandler> handler;

		bool attachCamera = false;
		std::shared_ptr<CubA4::game::controller::IContextActionsRules> controllerRules;
		ControllerFactory controllerFactory;

		bool chunkAnchor = false;
		bool chunkRenderAnchor = false;

		TickTypes tickTypes = +TickType::None;
	};
}