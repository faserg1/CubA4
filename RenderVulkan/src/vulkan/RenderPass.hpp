#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace CubA4::render::vulkan
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
