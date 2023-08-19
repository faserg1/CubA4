#pragma once

/** \file Интерфейс чанка
*/

#include <vector>
#include <memory>
#include <limits>
#include <world/Position.hpp>
#include <world/containers/IChunkBBaseContainer.hpp>
#include <world/data/IDataProvider.hpp>
#include <core/IIdentityiMap.hpp>

namespace CubA4::world
{
	class IChunkRange;

	struct BlockAt
	{
		CubA4::core::IIdentityiMap::IdType blockId = std::numeric_limits<CubA4::core::IIdentityiMap::IdType>::max();
		decltype(CubA4::world::BlockData::id) dataId = std::numeric_limits<decltype(CubA4::world::BlockData::id)>::max();
		CubA4::world::BlockInChunkPos pos;
		CubA4::world::Layer layer;
	};

	// Replace real block with id

	class IChunk
	{
	public:
		/**
		\brief Получение позиции чанка
		*/
		virtual const world::ChunkPos &getChunkPos() const = 0;
		/** \brief Получает используемые блоки в чанке
		 */
		virtual std::vector<CubA4::core::IIdentityiMap::IdType> getUsedBlocks() const = 0;
		/** \brief Получает диапазоны блоков в чанке.
		*/
		virtual std::vector<std::shared_ptr<const IChunkBBaseContainer>> getChunkBContainers() const = 0;
		virtual std::vector<std::shared_ptr<const IChunkBBaseContainer>> getChunkBContainers(CubA4::core::IIdentityiMap::IdType blockId) const = 0;
		virtual bool hasBlocksAt(world::BlockInChunkPos pos) const = 0;
		virtual bool hasBlocksAt(uint32_t index) const = 0;
		virtual std::vector<CubA4::world::BlockAt> getBlocksAt(world::BlockInChunkPos pos) const = 0;
		virtual CubA4::world::BlockAt getBlockAt(world::BlockInChunkPos pos, world::Layer layer) const = 0;

		virtual std::vector<CubA4::world::BlockAt> getBlocksAt(uint32_t index) const = 0;
		virtual CubA4::world::BlockAt getBlockAt(uint32_t index, world::Layer layer) const = 0;

		virtual const IDataProvider &getDataProvider() const = 0;
	protected:
		explicit IChunk() = default;
		virtual ~IChunk() = default;
	};
}
