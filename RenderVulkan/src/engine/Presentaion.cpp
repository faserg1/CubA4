#include "./Presentaion.hpp"
#include "../vulkan/Device.hpp"
#include "../vulkan/Swapchain.hpp"
#include "../vulkan/Semaphore.hpp"

#include <algorithm>

using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

Presentaion::Presentaion(std::shared_ptr<const VulkanDevice> device, std::shared_ptr<const VulkanSwapchain> swapchain) :
	device_(device), swapchain_(swapchain), timeout_(50)
{
	acquireSignalSemaphore_ = VulkanSemaphore::create(device);
}

Presentaion::~Presentaion()
{
	
}

std::shared_ptr<const VulkanSemaphore> Presentaion::getAcquireSignalSemaphore() const
{
	return acquireSignalSemaphore_;
}

void Presentaion::addAwaitSemaphore(std::shared_ptr<const VulkanSemaphore> semaphore)
{
	awaitSemaphores_.push_back(semaphore);
}

uint32_t Presentaion::acquire()
{
	VkAcquireNextImageInfoKHR info = {};
	info.sType = VK_STRUCTURE_TYPE_ACQUIRE_NEXT_IMAGE_INFO_KHR;
	info.swapchain = swapchain_->getSwapchain();
	info.semaphore = acquireSignalSemaphore_->getSemaphore();
	info.timeout = timeout_;
	uint32_t imageIndex;
	if (vkAcquireNextImage2KHR(device_->getDevice(), &info, &imageIndex) != VK_SUCCESS)
	{
		//TODO: [OOKAMI] Разберись с этим...
		return UINT32_MAX;
	}
	return imageIndex;
}

void Presentaion::send(uint32_t imageIndex)
{
	VkPresentInfoKHR info = {};
	std::vector<VkSemaphore> awaitSemaphores;
	std::transform(awaitSemaphores_.begin(), awaitSemaphores_.end(), awaitSemaphores.begin(),
		[](std::shared_ptr<const VulkanSemaphore> &semaphore) -> VkSemaphore
	{
		return semaphore->getSemaphore();
	});
	info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	info.swapchainCount = 1;
	VkSwapchainKHR swapchain = swapchain_->getSwapchain();
	info.pSwapchains = &swapchain;
	info.waitSemaphoreCount = awaitSemaphores.size();
	info.pWaitSemaphores = awaitSemaphores.data();
	info.pImageIndices = &imageIndex;
	if (vkQueuePresentKHR(device_->getQueue(), &info) != VK_SUCCESS)
	{
		//TODO: [OOKAMI] Разберись с этим...
	}
}