#ifndef RENDERVULKAN_IMEMORYPART_HPP
#define RENDERVULKAN_IMEMORYPART_HPP

#include <memory>
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Memory;
		}

		namespace engine
		{
			namespace memory
			{
				class IMemoryBlock;

				class IMemoryPart
				{
				public:
					virtual std::shared_ptr<vulkan::Memory> getMemory() const = 0;
					virtual VkDeviceSize getOffset() const = 0;
					virtual VkDeviceSize getSize() const = 0;
					virtual std::shared_ptr<const IMemoryBlock> getBlock() const = 0;
				protected:
					IMemoryPart() = default;
					virtual ~IMemoryPart() = default;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_IMEMORYPART_HPP
