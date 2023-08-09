#pragma once

#include <object/IEntityManager.hpp>
#include <system/IIdentityiMap.hpp>
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
		using IdType = CubA4::system::IIdentityiMap::IdType;
		EntityManager(CubA4::Core &core);

		std::shared_ptr<IEntityFactory> registerEntity(IdType factoryId, std::unique_ptr<const IEntityDefinition> &&def);
		EntityRenderManager &getEntityRenderManager();

		entt::registry &getRegistry();
	private:
		std::unique_ptr<EntityRenderManager> createRenderManager();
	private:
		CubA4::Core &core_;
		entt::registry registry_;
		std::unique_ptr<EntityRenderManager> entityRenderManager_;
	};
}