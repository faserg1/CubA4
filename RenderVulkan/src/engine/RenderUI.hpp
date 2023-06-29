#pragma once

#include <memory>
#include <engine/framebuffer/FramebufferManager.hpp>
#include <engine/pipeline/IMainEnginePipelineItem.hpp>
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
		class RenderUI : public virtual CubA4::render::engine::pipeline::IMainEnginePipelineItem
		{
		public:
			RenderUI(std::shared_ptr<const vulkan::Device> device,
				std::shared_ptr<FramebufferManager> framebufferManager,
				std::shared_ptr<RenderManager> renderManager);

			std::shared_ptr<const vulkan::Semaphore> render(uint32_t imgIndex, std::shared_ptr<const vulkan::Semaphore> awaitSemaphore) override;
		private:
			const std::shared_ptr<const vulkan::Device> device_;
			const std::shared_ptr<FramebufferManager> framebufferManager_;
			const std::shared_ptr<RenderManager> renderManager_;
		};
	}
}
