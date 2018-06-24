#ifndef VULKANSHADER_HPP
#define VULKANSHADER_HPP

#include <memory>
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanDevice;

			class VulkanShader
			{
			public:
				VkShaderModule getModule() const;

				static std::shared_ptr<VulkanShader> fromIrs(std::shared_ptr<VulkanDevice> device, const char *name);
			protected:
				explicit VulkanShader(std::shared_ptr<VulkanDevice> device, const void *data, size_t size);
				~VulkanShader();
			private:
				std::shared_ptr<VulkanDevice> device_;
				VkShaderModule module_;
			};
		}
	}
}

#endif // VULKANSHADER_HPP
