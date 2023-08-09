#pragma once

#include <object/IEntityFactory.hpp>
#include <object/Entity.hpp>
#include <object/IEntityDefinition.hpp>
#include <system/IIdentityiMap.hpp>
#include <object/EntityBuilderData.hpp>
#include <entt/entt.hpp>
#include <world/GlobalPosition.hpp>

namespace CubA4::object
{
	struct EntityBuilderData;

	class EntityFactory : public virtual IEntityFactory
	{
	public:
		using IdFactoryType = CubA4::system::IIdentityiMap::IdType;
		using IdWorldType = CubA4::system::IIdentityiMap::IdType;
		EntityFactory(IdFactoryType id, std::unique_ptr<const IEntityDefinition> &&def, entt::registry &registry, const EntityBuilderData &data);

		IdType getId() const override;
		std::wstring getName() const override;

		std::shared_ptr<Entity> create(IdWorldType idWorld, IdWorldType idDimension,
			const CubA4::world::GlobalPosition &pos) const;
	private:
		const IdFactoryType id_;
		entt::registry &registry_;
		std::unique_ptr<const IEntityDefinition> def_;
		EntityBuilderData data_;

		mutable IdFactoryType idGenerator_;
	};
}