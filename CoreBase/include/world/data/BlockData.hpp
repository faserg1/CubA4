#pragma once

#include <world/data/ObjectData.hpp>
#include <world/Position.hpp>

namespace CubA4::world
{
	/**
	 * 
	*/
	struct BlockData : ObjectData
	{
		/// Cannot be applied to multiple blocks, can be modified
		bool unique;
		constexpr friend std::strong_ordering operator<=>(const BlockData& a, const BlockData &b)
		{
			auto &aObject = (ObjectData &) a;
			auto &bObject = (ObjectData &) b;
			auto cmp = std::tie(aObject, a.unique) <=> std::tie(bObject, b.unique);
			if (cmp == std::weak_ordering::equivalent)
			{
				if (a.id == b.id)
					return std::strong_ordering::equal;
				return std::strong_ordering::equivalent;
			}
			if (cmp == std::weak_ordering::greater)
				return std::strong_ordering::greater;
			return std::strong_ordering::less;
		}
	};
}
