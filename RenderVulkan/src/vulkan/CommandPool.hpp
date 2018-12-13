#ifndef RENDERVULKAN_COMMANDPOOL_HPP
#define RENDERVULKAN_COMMANDPOOL_HPP

#include <memory>
#include <atomic>
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;

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
	}
}

#endif // RENDERVULKAN_COMMANDPOOL_HPP