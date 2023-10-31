#pragma once

#include <object/IEntityFactory.hpp>
#include <object/Entity.hpp>
#include <object/IEntityDefinition.hpp>
#include <core/IIdentityiMap.hpp>
#include <object/EntityBuilderData.hpp>
#include <entt/entt.hpp>
#include <world/GlobalPosition.hpp>

namespace CubA4::physics
{
	class IPhysicsEntityDefinition; 
}

namespace CubA4::render::engine
{
	class IRenderManager;
}

namespace CubA4::game::controller
{
	class IController;
}
namespace CubA4::object
{
	struct EntityBuilderData;

	class EntityFactory : public virtual IEntityFactory
	{
	public:
		struct Managers
		{
			std::weak_ptr<CubA4::render::engine::IRenderManager> renderManager;
			std::weak_ptr<CubA4::game::controller::IController> controller;
		};

		using IdFactoryType = CubA4::core::IIdentityiMap::IdType;
		using IdWorldType = CubA4::core::IIdentityiMap::IdType;
		EntityFactory(IdFactoryType id, std::unique_ptr<const IEntityDefinition> &&def, entt::registry &registry,
			EntityBuilderData &data, Managers managers);

		IdType getId() const override;
		std::wstring getName() const override;

		std::shared_ptr<Entity> create(IdWorldType idWorld, IdWorldType idDimension,
			const CubA4::world::GlobalPosition &pos) const;
	private:
		void preparePhysics(entt::entity handle, const CubA4::physics::IPhysicsEntityDefinition &def) const;
		void setupTicks(entt::entity handle, CubA4::object::TickTypes types) const;
	private:
		const IdFactoryType id_;
		entt::registry &registry_;
		std::unique_ptr<const IEntityDefinition> def_;
		EntityBuilderData data_;

		const Managers managers_;

		mutable IdFactoryType idGenerator_;
	};
}