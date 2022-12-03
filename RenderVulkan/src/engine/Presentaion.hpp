#pragma once

#include <memory>
#include <vector>
#include <vulkan/Device.hpp>
#include <vulkan/Swapchain.hpp>
#include <vulkan/Semaphore.hpp>

namespace CubA4::render::engine
{
	class Presentaion
	{
	public:
		explicit Presentaion(std::shared_ptr<const vulkan::Device> device);
		~Presentaion();

		std::shared_ptr<const vulkan::Semaphore> getAcquireSignalSemaphore() const;

		uint32_t acquire(std::shared_ptr<const vulkan::Swapchain> swapchain);
		void send(std::shared_ptr<const vulkan::Swapchain> swapchain, uint32_t imageIndex, std::vector<std::shared_ptr<const vulkan::Semaphore>> awaitSemaphores);
	protected:
		
	private:
		const std::shared_ptr<const vulkan::Device> device_;
		std::shared_ptr<vulkan::Semaphore> acquireSignalSemaphore_;
		uint32_t timeout_;
	};
}
