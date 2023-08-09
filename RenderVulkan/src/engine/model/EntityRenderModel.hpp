#pragma once

#include <engine/model/RenderModel.hpp>
#include <engine/material/Material.hpp>

namespace CubA4::render::engine::model
{
	class EntityRenderModel : public RenderModel
	{
		using IMaterial = CubA4::render::engine::material::IMaterial;
		using Material = CubA4::render::engine::material::Material;
	public:
		explicit EntityRenderModel(std::shared_ptr<const vulkan::Device> device, RenderModelData data, std::shared_ptr<const IMaterial> material);
		~EntityRenderModel();

		std::shared_ptr<const Material> getMaterial() const;
	private:
		std::shared_ptr<const Material> material_;
	};
}