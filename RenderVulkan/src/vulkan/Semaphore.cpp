#include "./Semaphore.hpp" 
#include "./Device.hpp" 
#include <stdexcept>
using namespace CubA4::render::vulkan;

Semaphore::Semaphore(VkSemaphore semaphore, std::weak_ptr<const Device> device) :
	device_(device), semaphore_(semaphore)
{
	
}

Semaphore::~Semaphore()
{
	if (auto dev = device_.lock())
		vkDestroySemaphore(dev->getDevice(), semaphore_, nullptr);
}

std::shared_ptr<Semaphore> Semaphore::create(std::shared_ptr<const Device> device)
{
	VkSemaphore semaphore;
	VkSemaphoreCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	if (vkCreateSemaphore(device->getDevice(), &info, nullptr, &semaphore) != VK_SUCCESS)
		throw std::runtime_error("Cannot create semaphore");
	return std::make_shared<Semaphore>(semaphore, device);
}

VkSemaphore Semaphore::getSemaphore() const
{
	return semaphore_;
}