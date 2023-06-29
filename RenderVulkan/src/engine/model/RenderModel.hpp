#pragma once

#include <engine/model/IRenderModel.hpp>
#include <vulkan/vulkan.h>
#include "../../vulkan/Device.hpp"
#include "../../vulkan/Memory.hpp"
#include <memory>
#include <string>

namespace CubA4::render::engine::model
{
	struct RenderModelData
	{
		// TODO: Use memory part
		std::shared_ptr<const vulkan::Memory> vertexBufferMemory;
		std::shared_ptr<const vulkan::Memory> indexBufferMemory;
		VkBuffer vertexBuffer;
		VkBuffer indexBuffer;
		std::string id;
		uint32_t vertexCount;
		uint32_t indexCount;
	};

	class RenderModel :
		public virtual IRenderModel
	{
	public:
		explicit RenderModel(std::shared_ptr<const vulkan::Device> device, RenderModelData data);
		~RenderModel();

		const std::string &getId() const override;
		uint32_t getVertexCount() const;
		uint32_t getIndexCount() const;
		void bind(VkCommandBuffer cmdBuffer, uint32_t index = 0) const;
	protected:
	private:
		std::shared_ptr<const vulkan::Device> device_;
		const RenderModelData data_;
	};
}

