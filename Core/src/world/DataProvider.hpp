#pragma once

#include <world/BlockDataStorage.hpp>
#include <memory>
#include <unordered_map>

namespace CubA4::world
{
	class DataProvider
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
