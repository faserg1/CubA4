#pragma once

#include <memory>
#include <object/IEntity.hpp>
#include <object/IEntityFactory.hpp>
#include <object/IEntityDefinition.hpp>

namespace CubA4::object
{
	class IEntityManager
	{
	public:
		virtual ~IEntityManager() = default;
	protected:
		explicit IEntityManager() = default;
	};
}
