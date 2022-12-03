#include <vulkan/Fence.hpp>
using namespace CubA4::render::vulkan;

Fence::Fence(std::shared_ptr<const Device> device, VkFenceCreateFlags flags) :
	device_(device)
{
	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	if (vkCreateFence(device_->getDevice(), &fenceInfo, nullptr, &fence_) != VK_SUCCESS)
	{
		// TODO: exception?
	}
}

Fence::~Fence()
{
	vkDestroyFence(device_->getDevice(), fence_, nullptr);
}

VkFence Fence::getFence() const
{
	return fence_;
}

VkResult Fence::wait(uint64_t timeout)
{
	return vkWaitForFences(device_->getDevice(), 1, &fence_, VK_TRUE, timeout);
}

void Fence::reset()
{
	vkResetFences(device_->getDevice(), 1, &fence_);
}