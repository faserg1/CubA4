#pragma once

#include <memory>
#include <string>
#include <world/IWorldControl.hpp>
#include <object/IEntity.hpp>
#include <object/IEntityFactory.hpp>
#include <core/IIdentityiMap.hpp>
#include <world/GlobalPosition.hpp>

namespace CubA4::game
{
	class IGameControl
	{
	public:
		using IdType = CubA4::core::IIdentityiMap::IdType;

		virtual ~IGameControl() = default;
		virtual bool requestWorldChange(const std::string &worldId, const std::string &dimId) = 0;
		virtual CubA4::world::IWorldControl &getWorldControl() = 0;
		// TODO: make co_async?
		virtual std::shared_ptr<object::IEntity> requestSpawn(std::shared_ptr<const object::IEntityFactory> factory, IdType dimensionId,
			const CubA4::world::GlobalPosition &pos) = 0;
		// TODO: make co_async?
		virtual bool requestDespawn(const object::IEntity &entity) = 0;
	protected:
		IGameControl() = default;
	};
}