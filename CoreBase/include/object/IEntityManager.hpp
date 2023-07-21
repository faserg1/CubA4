#pragma once

#include <memory>
#include <object/IEntity.hpp>
#include <object/IEntityDefinition.hpp>

namespace CubA4::object
{
	class IEntityManager
	{
	public:
		virtual ~IEntityManager() = default;

		virtual std::shared_ptr<IEntity> registerEntity(std::unique_ptr<IEntityDefinition> &&def) = 0;
	protected:
		explicit IEntityManager() = default;
	};
}
