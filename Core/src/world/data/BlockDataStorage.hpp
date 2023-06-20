#pragma once

#include <world/data/IBlockDataStorage.hpp>
#include <world/data/BlockData.hpp>
#include <unordered_map>
#include <memory>

namespace CubA4::world
{
	// TODO: Transaction?

	class BlockDataStorage : public virtual IBlockDataStorage
	{
		using BlockUsage = std::pair<std::shared_ptr<BlockData>, size_t>;
		using Storage = std::unordered_map<decltype(BlockData::id), BlockUsage>;
	public:
		explicit BlockDataStorage();
		~BlockDataStorage();

		std::shared_ptr<BlockData> getOrAdd(const BlockData &data, bool usage = false) override;
		std::shared_ptr<BlockData> modOrAdd(uint64_t id, const BlockData &data, bool usage = false) override;
		std::shared_ptr<BlockData> get(uint64_t id, bool usage = false) const override;
		bool remove(uint64_t id) override;

		// TODO: load/unload
	protected:
		std::shared_ptr<BlockData> add(BlockData data);
		std::shared_ptr<BlockData> find(const BlockData &data) const;
	private:
		uint64_t idAllocator_ = 0;
		mutable Storage storage_;
	};
}
