#include "./VulkanSemaphore.hpp"
#include "./VulkanDevice.hpp"
#include <stdexcept>
using namespace CubA4::render::vulkan;

VulkanSemaphore::VulkanSemaphore(VkSemaphore semaphore, std::weak_ptr<const VulkanDevice> device) :
	device_(device), semaphore_(semaphore)
{
	
}

VulkanSemaphore::~VulkanSemaphore()
{
	if (auto dev = device_.lock())
		vkDestroySemaphore(dev->getDevice(), semaphore_, nullptr);
}

std::shared_ptr<VulkanSemaphore> VulkanSemaphore::create(std::shared_ptr<const VulkanDevice> device)
{
	VkSemaphore semaphore;
	VkSemaphoreCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	if (vkCreateSemaphore(device->getDevice(), &info, nullptr, &semaphore) != VK_SUCCESS)
		throw std::runtime_error("Cannot create semaphore");
	return std::make_shared<VulkanSemaphore>(semaphore, device);
}

VkSemaphore VulkanSemaphore::getSemaphore() const
{
	return semaphore_;
}