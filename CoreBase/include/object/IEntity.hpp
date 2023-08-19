#pragma once

#include <core/IIdentityiMap.hpp>

namespace CubA4::object
{
	class IEntity
	{
	public:
		using IdType = CubA4::core::IIdentityiMap::IdType;

		virtual ~IEntity() = default;
		virtual IdType getEntityId() const = 0;
		virtual IdType getFactoryId() const = 0;
	protected:
		explicit IEntity() = default;
	};
}
