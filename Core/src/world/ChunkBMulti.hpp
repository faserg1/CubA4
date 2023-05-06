#pragma once

#include <world/IChunkBMulti.hpp>
#include <map>
#include <memory>

namespace CubA4::world
{
	class ChunkBMulti : public virtual IChunkBMulti
	{
	public:
		explicit ChunkBMulti(size_t id, std::shared_ptr<const object::IBlock> block, CubA4::world::Layer layer, std::map<world::BlockInChunkPos, std::shared_ptr<BlockData>> data);
		~ChunkBMulti();

		size_t getId() const override;
		std::shared_ptr<const object::IBlock> getBlock() const;
		uint32_t getBlockCount() const;
		CubA4::world::Layer getLayer() const;
		bool hasBlockAt(const world::BlockInChunkPos &pos) const;
		uint32_t getBlockIndex(const world::BlockInChunkPos &pos) const;
		CubA4::world::BlockInChunkPos getBlockPosition(uint32_t index) const;
		const BlockData &getBlockData(const world::BlockInChunkPos &pos) const;

		Iterator begin() const;
		Iterator end() const;
	private:
		class MultiIterator : public virtual IChunkBIterator
		{
		public:
			MultiIterator(const ChunkBMulti *multi, uint32_t index);
			std::unique_ptr<IChunkBIterator> copy() const override;
			bool equal(const IChunkBIterator *other) const override;
			void move(int32_t shift) override;
			const CubA4::world::BlockInChunkPos &get() const override;
		private:
			const ChunkBMulti *multi_;
			uint32_t index_;
			CubA4::world::BlockInChunkPos pos_;
		};
	private:
		const size_t id_;
		std::shared_ptr<const object::IBlock> block_;
		CubA4::world::Layer layer_;
		std::map<world::BlockInChunkPos, std::shared_ptr<BlockData>> data_;
	};
}
