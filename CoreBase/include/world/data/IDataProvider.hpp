#pragma once

#include <world/data/IBlockDataStorage.hpp>
#include <memory>

namespace CubA4::world
{
	class IDataProvider
	{
	public:
		virtual ~IDataProvider() = default;

		virtual const IBlockDataStorage *getBlockDataStorage(int64_t blockId) const = 0;
	protected:
		explicit IDataProvider() = default;
	};
}
