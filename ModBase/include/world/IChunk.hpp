#ifndef ICHUNK_HPP
#define ICHUNK_HPP

#include <vector>
#include <memory>

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
			struct ChunkPos
			{
				uint8_t x;
				uint8_t y;
				uint8_t z;
				uint8_t unused;
			};

			constexpr uint8_t ChunkSize = 16;

			class IChunk
			{
			public:
				virtual ~IChunk() = default;

				/* \brief Получает используемые блоки в чанке
				 */
				virtual std::vector<std::shared_ptr<const object::IBlock>> getUsedBlocks() const = 0;
				/* \brief Получает позиции блока в чанке
				 * \param usedBlock Используемый в чанке блок
				 * \param pos[out] Позиции в чанке
				 * \return Количество позиций в чанке
				*/
				virtual uint16_t getChunkPositions(const std::shared_ptr<const object::IBlock> usedBlock, const ChunkPos *&pos) const = 0;
			protected:
				explicit IChunk() = default;
			};
		}
	}
}

#endif // ICHUNK_HPP