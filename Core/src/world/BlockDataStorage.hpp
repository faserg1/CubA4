#pragma once

#include <world/BlockData.hpp>
#include <set>
#include <memory>

namespace CubA4::world
{
	// TODO: Transaction?
	class BlockDataStorage
	{
	public:
		explicit BlockDataStorage();
		~BlockDataStorage();

		std::shared_ptr<BlockData> findOrAdd(BlockData data);
		std::shared_ptr<BlockData> find(BlockData data) const;
		std::shared_ptr<BlockData> get(uint64_t id) const;
		bool remove(uint64_t id);
	protected:
		std::shared_ptr<BlockData> add(BlockData data);
	private:
		std::set<std::shared_ptr<BlockData>> dataStorage_;
		uint64_t idAllocator_ = 0;
	};
}
