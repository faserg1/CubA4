#include "./CommandPool.hpp"
#include "./Device.hpp"
using namespace CubA4::render::vulkan;

CommandPool::CommandPool(std::shared_ptr<const Device> device, VkCommandPoolCreateFlags flags):
	device_(device), flags_(flags), lock_(false)
{
	VkCommandPoolCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	info.flags = flags_;
	vkCreateCommandPool(device_->getDevice(), &info, nullptr, &pool_);
}

CommandPool::~CommandPool()
{
	vkDestroyCommandPool(device_->getDevice(), pool_, nullptr);
}

std::unique_ptr<const CommandPool::CommandPoolLock> CommandPool::tryLock() const
{
	if (lock_)
		return {};
	lock_ = true;
	return std::make_unique<CommandPool::CommandPoolLock>(lock_, shared_from_this());
}

bool CommandPool::isLocked() const
{
	return lock_;
}

VkCommandPool CommandPool::getPool() const
{
	return pool_;
}

bool CommandPool::allocate(uint32_t count, VkCommandBuffer *data, VkCommandBufferLevel level)
{
	VkCommandBufferAllocateInfo allocateInfo = {};
	allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocateInfo.commandPool = pool_;
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocateInfo.commandBufferCount = 1;
	return vkAllocateCommandBuffers(device_->getDevice(), &allocateInfo, data) == VK_SUCCESS;
}

VkCommandPoolCreateFlags CommandPool::getFlags() const
{
	return flags_;
}

CommandPool::CommandPoolLock::CommandPoolLock(std::atomic_bool &lock, std::shared_ptr<const CommandPool> pool) :
	lock_(lock), pool_(pool)
{
}

CommandPool::CommandPoolLock::~CommandPoolLock()
{
	lock_ = false;
}

std::shared_ptr<const CommandPool> CommandPool::CommandPoolLock::getPool() const
{
	return pool_;
}