#ifndef ICHUNK_HPP
#define ICHUNK_HPP

#include <vector>
#include <memory>
#include <type_traits>

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
			template <typename TPosType>
			struct BasePos
			{
				static_assert(std::is_arithmetic<TPosType>::value, "TPosType не является арифметическим типом!");
				TPosType x;
				TPosType y;
				TPosType z;
				friend bool operator==(const BasePos &one, const BasePos &other)
				{
					return one.x == other.x
						&& one.y == other.y
						&& one.z == other.z;
				}
			};

			/*Позиция блока в чанке */
			using BlockInChunkPos = BasePos<uint8_t>;
			/*Позиция чанка в мире */
			using ChunkPos = BasePos<uint64_t>;
			/*Глобальная позиция блока*/
			using BlockGlobalPos = BasePos<uint64_t>;

			/* Размер грани чанка */
			constexpr uint8_t ChunkSize = 16;

			class IChunk
			{
			public:
				virtual ~IChunk() = default;

				/* \brief Получает используемые блоки в чанке
				 */
				virtual std::vector<std::shared_ptr<const object::IBlock>> &&getUsedBlocks() const = 0;
				/* \brief Получает позиции блока в чанке
				 * \param usedBlock Используемый в чанке блок
				 * \param pos[out] Позиции в чанке
				 * \return Количество позиций в чанке
				*/
				virtual std::vector<BlockInChunkPos> &&getChunkPositions(const std::shared_ptr<const object::IBlock> usedBlock) const = 0;
				virtual const ChunkPos &getChunkPos() const = 0;
			protected:
				explicit IChunk() = default;
			};
		}
	}
}

#endif // ICHUNK_HPP