#ifndef MODBASE_ICHUNK_HPP
#define MODBASE_ICHUNK_HPP

/** \file Интерфейс чанка
*/

#include <vector>
#include <memory>
#include "Position.hpp"

namespace CubA4
{
	namespace mod
	{
		namespace object
		{
			class IBlock;
		}

		namespace world
		{
			class IChunk
			{
			public:
				/* \brief Получает используемые блоки в чанке
				 */
				virtual std::vector<std::shared_ptr<const object::IBlock>> getUsedBlocks() const = 0;
				/* \brief Получает позиции блока в чанке
				 * \param usedBlock Используемый в чанке блок
				 * \param pos[out] Позиции в чанке
				 * \return Количество позиций в чанке
				*/
				virtual std::vector<BlockInChunkPos> getChunkPositions(const std::shared_ptr<const object::IBlock> usedBlock) const = 0;
				virtual const ChunkPos &getChunkPos() const = 0;
			protected:
				explicit IChunk() = default;
				virtual ~IChunk() = default;
			};
		}
	}
}

#endif // MODBASE_ICHUNK_HPP