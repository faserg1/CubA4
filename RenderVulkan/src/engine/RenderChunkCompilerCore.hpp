#ifndef RENDERCHUNKCOMPILERCORE_HPP
#define RENDERCHUNKCOMPILERCORE_HPP

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include <atomic>
#include <cstddef>

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
			class RenderChunkCompilerCore
			{
				struct CommandPool;
			public:
			protected:
				explicit RenderChunkCompilerCore(std::shared_ptr<const vulkan::Device> device);
				~RenderChunkCompilerCore();

				std::shared_ptr<const CommandPool> lockCommandPool();
			protected:
				const std::shared_ptr<const vulkan::Device> device_;
			private:
				struct CommandPool
				{
					const VkCommandPool vkPool;
					std::atomic_bool available;
					CommandPool(VkCommandPool pool);
					CommandPool(CommandPool &&obj);
				};
			private:
				std::vector<CommandPool> commandPools_;
			private:
				void initCommandPools();
				void destroyCommandPools();

				
			};
		}
	}
}

#endif // RENDERCHUNKCOMPILERCORE_HPP
