#pragma once

#include <system/IIdentityiMap.hpp>

namespace CubA4::object
{
	struct WorldInfo
	{
		CubA4::system::IIdentityiMap::IdType worldId;
		CubA4::system::IIdentityiMap::IdType dimensionId;
		CubA4::system::IIdentityiMap::IdType factoryId;
		CubA4::system::IIdentityiMap::IdType entityId;
	};
}