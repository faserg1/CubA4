#ifndef RENDERVULKAN_RENDERCHUNKCOMPILERCORE_HPP
#define RENDERVULKAN_RENDERCHUNKCOMPILERCORE_HPP

#include <memory>
#include <vector>

#include "../../vulkan/CommandPool.hpp"
#include "../../vulkan/util/VulkanHandlerContainer.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
			class Memory;
		}

		namespace engine
		{
			namespace memory
			{
				class MemoryAllocator;
				class MemoryManager;
			}

			namespace pipeline
			{
				class RenderChunkCompilerCore
				{
					
				public:
				protected:
					explicit RenderChunkCompilerCore(std::shared_ptr<const vulkan::Device> device);
					~RenderChunkCompilerCore();

					std::unique_ptr<const vulkan::CommandPool::CommandPoolLock> lockCommandPool();
					vulkan::sVkDescriptorPool getDescriptorPool(const std::unique_ptr<const vulkan::CommandPool::CommandPoolLock> &lock);
				protected:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<memory::MemoryManager> memManager_;
				private:					
					std::vector<std::shared_ptr<vulkan::CommandPool>> commandPools_;
					std::vector<vulkan::sVkDescriptorPool> descriptorPools_;
				private:
					void initCommandPools();
					void initDescriptorPools();
				};
			}
		}
	}
}

#endif // RENDERVULKAN_RENDERCHUNKCOMPILERCORE_HPP
