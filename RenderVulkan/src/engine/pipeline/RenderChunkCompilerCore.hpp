#ifndef RENDERVULKAN_RENDERCHUNKCOMPILERCORE_HPP
#define RENDERVULKAN_RENDERCHUNKCOMPILERCORE_HPP

#include <memory>
#include <vector>

#include "../../vulkan/CommandPool.hpp"

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
			class MemoryAllocator;
			class MemoryManager;

			namespace pipeline
			{
				class RenderChunkCompilerCore
				{
					
				public:
				protected:
					explicit RenderChunkCompilerCore(std::shared_ptr<const vulkan::Device> device);
					~RenderChunkCompilerCore();

					std::unique_ptr<const vulkan::CommandPool::CommandPoolLock> lockCommandPool();
					VkDescriptorPool getDescriptorPool(const std::unique_ptr<const vulkan::CommandPool::CommandPoolLock> &lock);
				protected:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<MemoryManager> memManager_;
				private:					
					std::vector<std::shared_ptr<vulkan::CommandPool>> commandPools_;
					std::vector<VkDescriptorPool> descriptorPools_;
				private:
					void initCommandPools();

					void initDescriptorPools();
					void destroyDescriptorPools();
				};
			}
		}
	}
}

#endif // RENDERVULKAN_RENDERCHUNKCOMPILERCORE_HPP
