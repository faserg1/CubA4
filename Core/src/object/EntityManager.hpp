#pragma once

#include <object/IEntityManager.hpp>
#include <core/IIdentityiMap.hpp>
#include <object/EntityRenderManager.hpp>
#include <entt/entt.hpp>


namespace CubA4
{
	class Core;
}

namespace CubA4::object
{
	class EntityManager : public virtual IEntityManager
	{
	public:
		using IdType = CubA4::core::IIdentityiMap::IdType;
		EntityManager(CubA4::Core &core);

		std::shared_ptr<IEntityFactory> registerEntity(IdType factoryId, std::unique_ptr<const IEntityDefinition> &&def);
		EntityRenderManager &getEntityRenderManager();

		entt::registry &getRegistry();
	private:
		std::unique_ptr<EntityRenderManager> createRenderManager();
		void registerSignals();

		void onEntityUpdated(entt::registry &registry, entt::entity entity);
	private:
		CubA4::Core &core_;
		entt::registry registry_;
		entt::connection onEntityUpdated_;
		std::unique_ptr<EntityRenderManager> entityRenderManager_;
	};
}