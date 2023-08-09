#pragma once

#include <object/components/WorldInfo.hpp>
#include <functional>

namespace CubA4::render::engine::utils
{

	// TODO: make as std::hash

	class FactoryAndEntityIdHash
	{
		using EntityId = decltype(CubA4::object::WorldInfo::entityId);
		using FactoryId = decltype(CubA4::object::WorldInfo::factoryId);
	public:
		size_t operator()(const std::pair<EntityId, FactoryId> &pair) const
		{
			auto hash1 = std::hash<EntityId>{}(pair.first);
			auto hash2 = std::hash<FactoryId>{}(pair.second);

			if (hash1 != hash2) {
				return hash1 ^ hash2;             
			}
			
			// If hash1 == hash2, their XOR is zero.
			return hash1;
		}
	};
}

