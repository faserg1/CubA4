#ifndef RENDERVULKAN_RENDERMODEL_HPP
#define RENDERVULKAN_RENDERMODEL_HPP

#include <engine/model/IRenderModel.hpp>
#include <vulkan/vulkan.h>
#include <memory>
#include <string>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
			class Memory;
		}

		namespace engine
		{
			namespace model
			{
				struct RenderModelData
				{
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

					std::string getId() const override;
					uint32_t getVertexCount() const;
					uint32_t getIndexCount() const;
					void bind(VkCommandBuffer cmdBuffer, uint32_t index = 0) const;
				protected:
				private:
					std::shared_ptr<const vulkan::Device> device_;
					const RenderModelData data_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_RENDERMODEL_HPP
