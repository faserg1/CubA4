#include "./Presentaion.hpp"
#include "../vulkan/Device.hpp"
#include "../vulkan/Swapchain.hpp"
#include "../vulkan/Semaphore.hpp"

#include <algorithm>

using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

Presentaion::Presentaion(std::shared_ptr<const Device> device, std::shared_ptr<const Swapchain> swapchain) :
	device_(device), swapchain_(swapchain), timeout_(50)
{
	acquireSignalSemaphore_ = Semaphore::create(device);
}

Presentaion::~Presentaion()
{
	
}

std::shared_ptr<const Semaphore> Presentaion::getAcquireSignalSemaphore() const
{
	return acquireSignalSemaphore_;
}

uint32_t Presentaion::acquire()
{
	uint32_t imageIndex = 0;
	if (vkAcquireNextImageKHR(device_->getDevice(), swapchain_->getSwapchain(), timeout_,
		acquireSignalSemaphore_->getSemaphore(), VK_NULL_HANDLE, &imageIndex) != VK_SUCCESS)
	{
		//TODO: [OOKAMI] Разберись с этим...
		return UINT32_MAX;
	}
	return imageIndex;
}

void Presentaion::send(uint32_t imageIndex, std::vector<std::shared_ptr<const Semaphore>> awaitSemaphores)
{
	VkPresentInfoKHR info = {};
	std::vector<VkSemaphore> awaitVkSemaphores(awaitSemaphores.size());
	std::transform(awaitSemaphores.begin(), awaitSemaphores.end(), awaitVkSemaphores.begin(),
		[](std::shared_ptr<const Semaphore> &semaphore) -> VkSemaphore
	{
		return semaphore->getSemaphore();
	});
	info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	info.swapchainCount = 1;
	VkSwapchainKHR swapchain = swapchain_->getSwapchain();
	info.pSwapchains = &swapchain;
	info.waitSemaphoreCount = awaitVkSemaphores.size();
	info.pWaitSemaphores = awaitVkSemaphores.data();
	info.pImageIndices = &imageIndex;
	if (vkQueuePresentKHR(device_->getQueue(), &info) != VK_SUCCESS)
	{
		//TODO: [OOKAMI] Разберись с этим...
	}
}