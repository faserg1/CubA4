#ifndef RENDERVULKAN_IMEMORYBLOCK_HPP
#define RENDERVULKAN_IMEMORYBLOCK_HPP

#include <vulkan/vulkan.h>
#include <cstdint>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace memory
			{
				class IMemoryBlock
				{
				public:
					virtual VkMemoryPropertyFlags getFlags() const = 0;
					virtual uint32_t getMemoryTypeIndex() const = 0;
				protected:
					IMemoryBlock() = default;
					virtual ~IMemoryBlock() = default;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_IMEMORYBLOCK_HPP
