#pragma once

#include <core/IIdentityiMap.hpp>

namespace CubA4::object
{
	struct WorldInfo
	{
		CubA4::core::IIdentityiMap::IdType worldId;
		CubA4::core::IIdentityiMap::IdType dimensionId;
		CubA4::core::IIdentityiMap::IdType factoryId;
		CubA4::core::IIdentityiMap::IdType entityId;
	};
}