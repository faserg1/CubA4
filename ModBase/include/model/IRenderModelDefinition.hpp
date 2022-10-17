#pragma once

#include <model/IModelDefinition.hpp>
#include <world/Sides.hpp>
#include <world/BlockData.hpp>
#include <vector>

namespace CubA4
{
	namespace mod
	{
		namespace model
		{
			class IRenderModelDefinition :
				public virtual IModelDefinition
			{
			public:
				virtual std::vector<std::string> getUsedMaterials() const = 0;
				virtual const std::vector<core::model::Face> &getFaceIndices() const = 0;
				virtual const std::vector<core::model::Vertex> &getVertices() const = 0;
				virtual const std::vector<core::model::UVWCoords> &getUVWCoords() const = 0;
				/**
				 * @brief Возвращает стороны, которые будут использованы для отображения блока
				 * @return std::vector<unsigned short> 
				 */
				virtual std::vector<unsigned short> getFaces(const std::string &materialId, std::vector<core::world::BlockSide> hiddenSides, const core::world::BlockData& data) const = 0;
				virtual std::vector<core::world::BlockSide> getNonOpaqueSide(const std::string &materialId, const core::world::BlockData& data) const = 0;
			protected:
				explicit IRenderModelDefinition() = default;
				virtual ~IRenderModelDefinition() = default;
			private:
			};
		}
	}
}
