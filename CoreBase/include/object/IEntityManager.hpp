#pragma once

#include <memory>
#include <object/IEntity.hpp>
#include <object/IEntityFactory.hpp>
#include <object/IEntityDefinition.hpp>

namespace CubA4::world
{
	class IWorld;
	class IDimension;
}

namespace CubA4::object
{
	class IEntityManager
	{
	public:
		virtual ~IEntityManager() = default;

		virtual std::shared_ptr<const CubA4::world::IWorld> getCurrentWorld(IEntity &entity) const = 0;
		virtual std::shared_ptr<const CubA4::world::IDimension> getCurrentDimension(IEntity &entity) const = 0;
	protected:
		explicit IEntityManager() = default;
	};
}
