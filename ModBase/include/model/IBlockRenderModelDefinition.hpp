#pragma once

#include <model/IRenderModelDefinition.hpp>
#include <world/Sides.hpp>
#include <world/data/BlockData.hpp>
#include <vector>

namespace CubA4::model
{
	class IBlockRenderModelDefinition :
		public virtual IRenderModelDefinition
	{
	public:
		/**
		 * @brief Возвращает стороны, которые будут использованы для отображения блока
		 * @return std::vector<unsigned short> 
		 */
		virtual std::vector<unsigned short> getFaces(const std::string &materialId, world::BlockSides hiddenSides, const world::BlockData& data) const = 0;
		virtual world::BlockSides getNonOpaqueSide(const world::BlockData& data) const = 0;
	protected:
		explicit IBlockRenderModelDefinition() = default;
		virtual ~IBlockRenderModelDefinition() = default;
	private:
	};
}
