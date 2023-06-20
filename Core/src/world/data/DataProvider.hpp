#pragma once

#include <world/data/IDataProvider.hpp>
#include <world/data/BlockDataStorage.hpp>
#include <memory>
#include <unordered_map>

namespace CubA4::world
{
	class DataProvider : public virtual IDataProvider
	{
	public:
		explicit DataProvider();
		~DataProvider();

		BlockDataStorage &getBlockDataStorage(int64_t blockId);
		const BlockDataStorage *getBlockDataStorage(int64_t blockId) const;

		// TODO: load/unload
	private:
		std::unordered_map<int64_t, std::unique_ptr<BlockDataStorage>> blockDataStorages_;
	};
}
