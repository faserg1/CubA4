#pragma once

#include <object/IEntityManager.hpp>
#include <system/IIdentityiMap.hpp>
#include <entt/entt.hpp>

namespace CubA4::object
{
	class EntityManager : public virtual IEntityManager
	{
	public:
		using IdType = CubA4::system::IIdentityiMap::IdType;
		EntityManager();

		std::shared_ptr<IEntityFactory> registerEntity(IdType factoryId, std::unique_ptr<const IEntityDefinition> &&def);
	private:
		entt::registry registry_;
	};
}