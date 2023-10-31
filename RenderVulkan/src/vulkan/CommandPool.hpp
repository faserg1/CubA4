#pragma once

#include <memory>
#include <mutex>
#include <vulkan/vulkan.h>
#include <vulkan/Device.hpp>

namespace CubA4::render::vulkan
{
	class CommandPool :
		public std::enable_shared_from_this<CommandPool>
	{
	public:
		class CommandPoolLock;
		class ConstCommandPoolLock;
	public:
		explicit CommandPool(std::shared_ptr<const Device> device, VkCommandPoolCreateFlags flags);
		~CommandPool();

		std::unique_ptr<const ConstCommandPoolLock> tryLock() const;
		std::unique_ptr<CommandPoolLock> tryLock();
		std::unique_ptr<const ConstCommandPoolLock> lock() const;
		std::unique_ptr<CommandPoolLock> lock();
		VkCommandPool getPool() const;
		bool allocate(uint32_t count, VkCommandBuffer *data, VkCommandBufferLevel level = VK_COMMAND_BUFFER_LEVEL_PRIMARY);
		void free(uint32_t count, const VkCommandBuffer *data);
		VkCommandPoolCreateFlags getFlags() const;
	protected:
	private:
		const std::shared_ptr<const Device> device_;
		const VkCommandPoolCreateFlags flags_;
		VkCommandPool pool_;
		mutable std::mutex mutex_;
	public:
		class CommandPoolLock
		{
		public:
			CommandPoolLock(std::mutex &mutex, bool locked, std::shared_ptr<CommandPool> pool);
			~CommandPoolLock();
			std::shared_ptr<CommandPool> getPool() const;
		private:
			std::mutex &mutex_;
			const std::shared_ptr<CommandPool> pool_;
		};
		class ConstCommandPoolLock
		{
		public:
			ConstCommandPoolLock(std::mutex &mutex, bool locked, std::shared_ptr<const CommandPool> pool);
			~ConstCommandPoolLock();
			std::shared_ptr<const CommandPool> getPool() const;
		private:
			std::mutex &mutex_;
			const std::shared_ptr<const CommandPool> pool_;
		};
	};
}
