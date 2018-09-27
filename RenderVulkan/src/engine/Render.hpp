#ifndef RENDER_HPP
#define RENDER_HPP

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
			class Swapchain;
			class Semaphore;
			class RenderPass;
		}

		namespace engine
		{
			class Render
			{
			public:
				explicit Render(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<const vulkan::Swapchain> swapchain);
				explicit Render(const Render &) = delete;
				~Render();

				void record(uint32_t imgIndex);
				std::shared_ptr<const vulkan::Semaphore> send(uint32_t imgIndex, std::shared_ptr<const vulkan::Semaphore> awaitSemaphore);

				std::shared_ptr<const vulkan::RenderPass> getRenderPass() const;
			protected:
				void createMainCommandPool();
				void destroyMainCommandPool();

				void createFramebuffers();
				void destroyFramebuffers();

				void createRenderPass();
				void destroyRenderPass();
			private:
				const std::shared_ptr<const vulkan::Device> device_;
				const std::shared_ptr<const vulkan::Swapchain> swapchain_;
				VkCommandPool mainCommandPool_;

				struct FramebufferData
				{
					VkFence fence;
					VkFramebuffer framebuffer;
					VkImage image;
					VkImageView imageView;
					VkCommandBuffer cmdBuffer;
					std::shared_ptr<const vulkan::Semaphore> renderDoneSemaphore;
				};
				std::vector<FramebufferData> framebuffersData_;

				std::shared_ptr<const vulkan::RenderPass> renderPass_;
			};
		}
	}
}

#endif // RENDER_HPP
