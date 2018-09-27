#ifndef RENDERPASS_HPP
#define RENDERPASS_HPP

#include <vulkan/vulkan.h>
#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;

			class RenderPass
			{
			public:
				explicit RenderPass(std::shared_ptr<const Device> device, VkRenderPass renderPass);
				~RenderPass();

				VkRenderPass getRenderPass() const;
			protected:
			private:
				const std::shared_ptr<const Device> device_;
				const VkRenderPass renderPass_;
			};
		}
	}
}

#endif // RENDERPASS_HPP
