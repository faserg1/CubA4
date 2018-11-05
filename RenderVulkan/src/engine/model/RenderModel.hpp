#ifndef RENDERMODEL_HPP
#define RENDERMODEL_HPP

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
				class RenderModel :
					public virtual IRenderModel
				{
				public:
					explicit RenderModel(std::shared_ptr<const vulkan::Device> device,
						std::shared_ptr<const vulkan::Memory> vertexBufferMemory,
						std::shared_ptr<const vulkan::Memory> indexBufferMemory,
						VkBuffer vertexBuffer,
						VkBuffer indexBuffer,
						const std::string &id);
					~RenderModel();

					std::string getId() const override;
					void bind(VkCommandBuffer cmdBuffer, uint32_t index = 0);
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<const vulkan::Memory> vertexBufferMemory_;
					const std::shared_ptr<const vulkan::Memory> indexBufferMemory_;
					const VkBuffer vertexBuffer_;
					const VkBuffer indexBuffer_;
					const std::string id_;
				};
			}
		}
	}
}

#endif // RENDERMODEL_HPP
