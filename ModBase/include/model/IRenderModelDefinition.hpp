#pragma once

#include <model/IModelDefinition.hpp>
#include <world/Sides.hpp>
#include <world/data/BlockData.hpp>
#include <vector>
#include <memory>

namespace CubA4::render::engine::material
{
	class IMaterial;
}

namespace CubA4::model
{
	class IRenderModelDefinition :
		public virtual IModelDefinition
	{
	public:
		using RMaterial = std::shared_ptr<const CubA4::render::engine::material::IMaterial>;

		// TODO: for entity create separete interface with meshes -> materials

		virtual std::vector<std::string> getUsedMaterials() const = 0;
		virtual const FaceIndices &getFaceIndices() const = 0;
		virtual const std::vector<Vertex> &getVertices() const = 0;
		virtual const std::vector<UVWCoords> &getUVWCoords() const = 0;
		virtual RMaterial getMaterial(const std::string &materialId) const = 0;
	protected:
		explicit IRenderModelDefinition() = default;
		virtual ~IRenderModelDefinition() = default;
	private:
	};
}
