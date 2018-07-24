#ifndef PRESENTAION_HPP
#define PRESENTAION_HPP

#include <memory>
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
		}

		namespace engine
		{
			class Presentaion
			{
			public:
				explicit Presentaion(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<const vulkan::Swapchain> swapchain);
				~Presentaion();

				std::shared_ptr<const vulkan::Semaphore> getAcquireSignalSemaphore() const;

				uint32_t acquire();
				void send(uint32_t imageIndex, std::vector<std::shared_ptr<const vulkan::Semaphore>> awaitSemaphores);
			protected:
				
			private:
				const std::shared_ptr<const vulkan::Device> device_;
				const std::shared_ptr<const vulkan::Swapchain> swapchain_;
				std::shared_ptr<vulkan::Semaphore> acquireSignalSemaphore_;
				uint32_t timeout_;
			};
		}
	}
}

#endif // PRESENTAION_HPP
