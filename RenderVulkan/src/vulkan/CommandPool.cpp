#include "./CommandPool.hpp"
#include "./Device.hpp"
using namespace CubA4::render::vulkan;

CommandPool::CommandPool(std::shared_ptr<const Device> device, VkCommandPoolCreateFlags flags):
	device_(device), flags_(flags)
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
	if (!mutex_.try_lock())
		return {};
	return std::make_unique<CommandPool::CommandPoolLock>(mutex_, true, shared_from_this());
}

std::unique_ptr<CommandPool::CommandPoolLock> CommandPool::tryLock()
{
	if (!mutex_.try_lock())
		return {};
	return std::make_unique<CommandPool::CommandPoolLock>(mutex_, true, shared_from_this());
}

std::unique_ptr<const CommandPool::CommandPoolLock> CommandPool::lock() const
{
	return std::make_unique<CommandPool::CommandPoolLock>(mutex_, false, shared_from_this());
}

std::unique_ptr<CommandPool::CommandPoolLock> CommandPool::lock()
{
	return std::make_unique<CommandPool::CommandPoolLock>(mutex_, false, shared_from_this());
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
	allocateInfo.level = level;
	allocateInfo.commandBufferCount = count;
	return vkAllocateCommandBuffers(device_->getDevice(), &allocateInfo, data) == VK_SUCCESS;
}

void CommandPool::free(uint32_t count, const VkCommandBuffer *data)
{
	return vkFreeCommandBuffers(device_->getDevice(), pool_, count, data);
}

VkCommandPoolCreateFlags CommandPool::getFlags() const
{
	return flags_;
}

CommandPool::CommandPoolLock::CommandPoolLock(std::mutex &mutex, bool locked, std::shared_ptr<const CommandPool> pool) :
	mutex_(mutex), pool_(pool)
{
	if (!locked)
		mutex.lock();
}

CommandPool::CommandPoolLock::~CommandPoolLock()
{
	mutex_.unlock();
}

std::shared_ptr<const CommandPool> CommandPool::CommandPoolLock::getPool() const
{
	return pool_;
}