#pragma once

#include <object/IEntity.hpp>
#include <entt/entt.hpp>

namespace CubA4::object
{
	class Entity : public virtual IEntity
	{
	public:
		Entity(entt::registry &registry, entt::entity entity);
		~Entity();

		IdType getEntityId() const override;
		IdType getFactoryId() const override;
	private:
		entt::registry &registry_;
		entt::entity entity_;
	};
}