#pragma once

#include <world/containers/IChunkBBaseContainer.hpp>
#include <array>
#include <memory>

namespace CubA4::world
{
	class ChunkBMutable : public virtual IChunkBBaseContainer
	{
	public:
		explicit ChunkBMutable(size_t id, CubA4::system::IIdentityiMap::IdType blockId, CubA4::world::Layer layer);
		~ChunkBMutable();

		size_t getId() const override;
		bool isIndexGlobal() const override;
		CubA4::system::IIdentityiMap::IdType getBlockId() const override;
		uint32_t getBlockCount() const override;
		CubA4::world::Layer getLayer() const override;
		bool hasBlockAt(const world::BlockInChunkPos &pos) const override;
		bool hasBlockAt(uint32_t index) const override;
		uint32_t getBlockIndex(const world::BlockInChunkPos &pos) const override;
		uint32_t getBlockLocalIndex(const world::BlockInChunkPos &pos) const override;
		CubA4::world::BlockInChunkPos getBlockPosition(uint32_t index) const override;
		CubA4::world::BlockInChunkPos getBlockPositionLocal(uint32_t localIndex) const override;
		decltype(BlockData::id) getBlockData(const world::BlockInChunkPos &pos) const override;
		decltype(BlockData::id) getBlockData(uint32_t index) const override;

		void setBlockAt(const world::BlockInChunkPos &pos, decltype(BlockData::id) dataId);
		void setBlockAt(uint32_t index, decltype(BlockData::id) dataId);
		void deleteBlockAt(const world::BlockInChunkPos &pos);
		void deleteBlockAt(uint32_t index);

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
		CubA4::system::IIdentityiMap::IdType blockId_;
		CubA4::world::Layer layer_;
		std::array<decltype(BlockData::id), CubA4::world::ChunkCube> blockMap_;
		uint32_t blockCount_ = 0;
	};
}
