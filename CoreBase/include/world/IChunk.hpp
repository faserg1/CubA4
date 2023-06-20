#pragma once

/** \file Интерфейс чанка
*/

#include <vector>
#include <memory>
#include <world/Position.hpp>
#include <world/containers/IChunkBBaseContainer.hpp>
#include <world/data/IDataProvider.hpp>
#include <object/IBlock.hpp>

namespace CubA4::world
{
	class IChunkRange;

	struct BlockAt
	{
		std::shared_ptr<const object::IBlock> block;
		CubA4::world::BlockInChunkPos pos;
		CubA4::world::Layer layer;
	};

	class IChunk
	{
	public:
		/**
		\brief Получение позиции чанка
		*/
		virtual const world::ChunkPos &getChunkPos() const = 0;
		/** \brief Получает используемые блоки в чанке
		 */
		virtual std::vector<std::shared_ptr<const object::IBlock>> getUsedBlocks() const = 0;
		/** \brief Получает диапазоны блоков в чанке.
		*/
		virtual std::vector<std::shared_ptr<const IChunkBBaseContainer>> getChunkBContainers() const = 0;
		virtual std::vector<std::shared_ptr<const IChunkBBaseContainer>> getChunkBContainers(const std::shared_ptr<const object::IBlock> usedBlock) const = 0;
		virtual bool hasBlocksAt(world::BlockInChunkPos pos) const = 0;
		virtual bool hasBlocksAt(uint32_t index) const = 0;
		virtual std::vector<CubA4::world::BlockAt> getBlocksAt(world::BlockInChunkPos pos) const = 0;
		virtual CubA4::world::BlockAt getBlockAt(world::BlockInChunkPos pos, world::Layer layer) const = 0;

		virtual const IDataProvider &getDataProvider() const = 0;
	protected:
		explicit IChunk() = default;
		virtual ~IChunk() = default;
	};
}
