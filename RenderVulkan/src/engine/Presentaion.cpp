#include <engine/Presentaion.hpp>
#include <algorithm>

using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

Presentaion::Presentaion(std::shared_ptr<const Device> device) :
	device_(device), timeout_(50)
{
	acquireSignalSemaphore_ = Semaphore::create(device);
	device_->getMarker().setName(acquireSignalSemaphore_->getSemaphore(), "[Presentaion] Acquire semaphore");
}

Presentaion::~Presentaion()
{
	
}

std::shared_ptr<const Semaphore> Presentaion::getAcquireSignalSemaphore() const
{
	return acquireSignalSemaphore_;
}

uint32_t Presentaion::acquire(std::shared_ptr<const vulkan::Swapchain> swapchain)
{
	uint32_t imageIndex = 0;
	if (auto result = vkAcquireNextImageKHR(device_->getDevice(), swapchain->getSwapchain(), timeout_,
		acquireSignalSemaphore_->getSemaphore(), VK_NULL_HANDLE, &imageIndex); result != VK_SUCCESS)
	{
		//TODO: [OOKAMI] Разберись с этим...
		return UINT32_MAX;
	}
	return imageIndex;
}

void Presentaion::send(std::shared_ptr<const vulkan::Swapchain> swapchain, uint32_t imageIndex, std::vector<std::shared_ptr<const Semaphore>> awaitSemaphores)
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
	VkSwapchainKHR vkSwapchain = swapchain->getSwapchain();
	info.pSwapchains = &vkSwapchain;
	info.waitSemaphoreCount = static_cast<uint32_t>(awaitVkSemaphores.size());
	info.pWaitSemaphores = awaitVkSemaphores.data();
	info.pImageIndices = &imageIndex;

	auto q = device_->getQueue();

	if (auto result = vkQueuePresentKHR(q->get(), &info); result != VK_SUCCESS)
	{
		//TODO: [OOKAMI] Разберись с этим...
	}
}