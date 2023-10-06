#pragma once

#include <core/IIdentityiMap.hpp>

namespace CubA4::object
{
	class IEntity;

	struct Transform;

	class IEntityHandler
	{
	public:
		using IdType = CubA4::core::IIdentityiMap::IdType;

		virtual ~IEntityHandler() = default;
		
		virtual void onTransformChanged(const IEntity &entity, const Transform& tr) {}
	protected:
		explicit IEntityHandler() = default;
	};
}
