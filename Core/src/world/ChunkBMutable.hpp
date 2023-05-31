#pragma once

#include <world/IChunkBMulti.hpp>
#include <map>
#include <unordered_map>
#include <memory>

namespace CubA4::world
{
	class ChunkBMutable : public virtual IChunkBMulti
	{
		struct BlockDataInternal
		{
			std::shared_ptr<BlockData> data;
			size_t usage = 0;
		};
	public:
		explicit ChunkBMutable(size_t id, std::shared_ptr<const object::IBlock> block);
		~ChunkBMutable();

		size_t getId() const override;
		std::shared_ptr<const object::IBlock> getBlock() const override;
		uint32_t getBlockCount() const override;
		CubA4::world::Layer getLayer() const override;
		bool hasBlockAt(const world::BlockInChunkPos &pos) const override;
		uint32_t getBlockIndex(const world::BlockInChunkPos &pos) const override;
		CubA4::world::BlockInChunkPos getBlockPosition(uint32_t index) const override;
		const BlockData &getBlockData(const world::BlockInChunkPos &pos) const override;

		void addBlockAt(const world::BlockInChunkPos &pos, std::shared_ptr<BlockData> data);
		void deleteBlockAt(const world::BlockInChunkPos &pos);

		Iterator begin() const override;
		Iterator end() const override;
	private:


		class MutableIterator : public virtual IChunkBIterator
		{
		public:
			MutableIterator(const ChunkBMutable *cMutable, uint32_t index);
			std::unique_ptr<IChunkBIterator> copy() const override;
			bool equal(const IChunkBIterator *other) const override;
			void move(int32_t shift) override;
			const CubA4::world::BlockInChunkPos &get() const override;
		private:
			const ChunkBMutable *mutable_;
			uint32_t index_;
			CubA4::world::BlockInChunkPos pos_;
		};
	private:
		const size_t id_;
		std::shared_ptr<const object::IBlock> block_;
		// Layer for mutable are always 0
		CubA4::world::Layer layer_ = 0;
		std::map<world::BlockInChunkPos, decltype(BlockData::id)> blockMap_;
		std::unordered_map<decltype(BlockData::id), BlockDataInternal> dataMap_;
	};
}
