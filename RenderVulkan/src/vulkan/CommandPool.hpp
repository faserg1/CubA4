#pragma once

#include <memory>
#include <atomic>
#include <vulkan/vulkan.h>
#include <vulkan/Device.hpp>

namespace CubA4::render::vulkan
{
	class CommandPool :
		public std::enable_shared_from_this<CommandPool>
	{
	public:
		class CommandPoolLock;
	public:
		explicit CommandPool(std::shared_ptr<const Device> device, VkCommandPoolCreateFlags flags);
		~CommandPool();

		std::unique_ptr<const CommandPoolLock> tryLock() const;
		bool isLocked() const;
		VkCommandPool getPool() const;
		VkCommandPoolCreateFlags getFlags() const;
	protected:
	private:
		const std::shared_ptr<const Device> device_;
		const VkCommandPoolCreateFlags flags_;
		VkCommandPool pool_;
		mutable std::atomic_bool lock_;
	public:
		class CommandPoolLock
		{
		public:
			CommandPoolLock(std::atomic_bool &lock, std::shared_ptr<const CommandPool> pool);
			~CommandPoolLock();
			std::shared_ptr<const CommandPool> getPool() const;
		private:
			std::atomic_bool &lock_;
			const std::shared_ptr<const CommandPool> pool_;
		};
	};
}
