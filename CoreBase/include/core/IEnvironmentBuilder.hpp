#pragma once

#include <memory>
#include <string>

#include <object/IObject.hpp>
#include <world/IWorld.hpp>
#include <object/IEntityDefinition.hpp>
#include <object/IEntityFactory.hpp>
#include <world/IWorldDefinition.hpp>
#include <game/controller/IRootActions.hpp>

namespace CubA4::render
{
	class IRenderInfo;
}

namespace CubA4::render::engine
{
	class IRenderManager;
}

namespace CubA4::core
{
	class IEnvironmentBuilder
	{
	public:
		virtual const CubA4::render::IRenderInfo &getRenderInfo() const = 0;
		virtual std::shared_ptr<CubA4::render::engine::IRenderManager> getRenderManager() const = 0;
		virtual std::shared_ptr<CubA4::game::controller::IRootActions> getActions() const = 0;

		virtual bool registerObject(std::shared_ptr<CubA4::object::IObject> object) = 0;

		virtual std::shared_ptr<const CubA4::world::IWorld> createWorld(std::shared_ptr<const CubA4::world::IWorldDefinition> worldDef) = 0;
		virtual std::shared_ptr<const CubA4::object::IEntityFactory> registerEntity(std::unique_ptr<const CubA4::object::IEntityDefinition> &&entityDef) = 0;
	protected:
		explicit IEnvironmentBuilder() = default;
		virtual ~IEnvironmentBuilder() = default;
	private:
	};
}
