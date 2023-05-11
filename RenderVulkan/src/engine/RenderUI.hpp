#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include <atomic>

namespace CubA4::render
{
	namespace config
	{
		class IRenderConfig;
	}

	namespace vulkan
	{
		class Device;
		class Memory;
		class Swapchain;
		class Semaphore;
		class RenderPass;
	}

	namespace engine
	{
		class RenderUI
		{
		public:
			RenderUI(std::shared_ptr<const vulkan::Device> device);
			void recordApplyUI(VkCommandBuffer cmd);

		private:
			const std::shared_ptr<const vulkan::Device> device_;
		};
	}
}
