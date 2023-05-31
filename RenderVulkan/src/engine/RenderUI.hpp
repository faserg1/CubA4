#pragma once

#include <memory>
#include <engine/FramebufferManager.hpp>
#include <engine/RenderManager.hpp>
#include <vulkan/Device.hpp>
#include <vulkan/Semaphore.hpp>

namespace CubA4::render
{
	namespace config
	{
		class IRenderConfig;
	}

	namespace engine
	{
		class RenderUI
		{
		public:
			RenderUI(std::shared_ptr<const vulkan::Device> device,
				std::shared_ptr<FramebufferManager> framebufferManager,
				std::shared_ptr<RenderManager> renderManager);

			std::shared_ptr<vulkan::Semaphore> render(uint32_t imgIndex, std::shared_ptr<const vulkan::Semaphore> awaitSemaphore);
		private:
			const std::shared_ptr<const vulkan::Device> device_;
			const std::shared_ptr<FramebufferManager> framebufferManager_;
			const std::shared_ptr<RenderManager> renderManager_;
		};
	}
}
