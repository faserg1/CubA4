#pragma once

#include <world/IBlockDataStorage.hpp>
#include <world/BlockData.hpp>
#include <set>
#include <memory>

namespace CubA4::world
{
	// TODO: Transaction?

	class BlockDataStorage : public virtual IBlockDataStorage
	{
	public:
		explicit BlockDataStorage();
		~BlockDataStorage();

		std::shared_ptr<BlockData> getOrAdd(const BlockData &data) override;
		std::shared_ptr<BlockData> modOrAdd(uint64_t id, const BlockData &data) override;
		std::shared_ptr<BlockData> get(uint64_t id) const  override;
		bool remove(uint64_t id)  override;

		const Storage &getStorage() const override;

		// TODO: load/unload
	protected:
		std::shared_ptr<BlockData> add(BlockData data);
		std::shared_ptr<BlockData> mod(uint64_t id, const  BlockData &data);
		std::shared_ptr<BlockData> find(const BlockData &data) const;
	private:
		Storage dataStorage_;
		uint64_t idAllocator_ = 0;
	};
}
