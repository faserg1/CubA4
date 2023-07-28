#pragma once

#include <object/IEntityFactory.hpp>
#include <object/Entity.hpp>
#include <object/IEntityDefinition.hpp>
#include <system/IIdentityiMap.hpp>
#include <entt/entt.hpp>

namespace CubA4::object
{
	class EntityFactory : public virtual IEntityFactory
	{
	public:
		using IdFactoryType = CubA4::system::IIdentityiMap::IdType;
		EntityFactory(IdFactoryType id, std::unique_ptr<const IEntityDefinition> &&def, entt::registry &registry);

		IdType getId() const override;
		std::wstring getName() const override;

		std::unique_ptr<Entity> create();
	private:
		const IdFactoryType id_;
		entt::registry &registry_;
		std::unique_ptr<const IEntityDefinition> def_;

		IdFactoryType idGenerator_;
	};
}