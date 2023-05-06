#pragma once

#include <world/IBlockDataStorage.hpp>
#include <util/ITransaction.hpp>

namespace CubA4::world
{
	class BlockDataStorageTransaction :
		public virtual IBlockDataStorage,
		public virtual CubA4::util::ITransaction
	{
	public:
		explicit BlockDataStorageTransaction();
		~BlockDataStorageTransaction();
	};
}
