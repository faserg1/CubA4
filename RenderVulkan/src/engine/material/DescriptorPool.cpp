#include <engine/material/DescriptorPool.hpp>
using namespace CubA4::render::engine::material;

DescriptorPool::DescriptorPool(std::shared_ptr<const vulkan::Device> device) :
	device_(device)
{
	
}

DescriptorPool::~DescriptorPool()
{
	vkDestroyDescriptorPool(device_->getDevice(), pool_, nullptr);
}

VkDescriptorPool DescriptorPool::get() const
{
	return pool_;
}

void DescriptorPool::createPool()
{
	VkDescriptorPoolCreateInfo poolCreateInfo = {};
	
	poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolCreateInfo.maxSets = getMaxSetCount();
	poolCreateInfo.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;

	auto sizes = getPoolSizes();

	poolCreateInfo.poolSizeCount = static_cast<uint32_t>(sizes.size());
	poolCreateInfo.pPoolSizes = sizes.data();

	if (vkCreateDescriptorPool(device_->getDevice(), &poolCreateInfo, nullptr, &pool_) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
		return;
	}

	device_->getMarker().setName(pool_, "Textures pool");
}