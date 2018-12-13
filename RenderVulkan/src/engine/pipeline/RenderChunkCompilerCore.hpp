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
		}

		namespace engine
		{
			namespace pipeline
			{
				class RenderChunkCompilerCore
				{
					
				public:
				protected:
					explicit RenderChunkCompilerCore(std::shared_ptr<const vulkan::Device> device);
					~RenderChunkCompilerCore();

					std::unique_ptr<const vulkan::CommandPool::CommandPoolLock> lockCommandPool();
				protected:
					const std::shared_ptr<const vulkan::Device> device_;
				private:
					std::vector<std::shared_ptr<vulkan::CommandPool>> commandPools_;
				private:
					void initCommandPools();
				};
			}
		}
	}
}

#endif // RENDERVULKAN_RENDERCHUNKCOMPILERCORE_HPP
