#ifndef RENDERVULKAN_MEMORYPART_HPP
#define RENDERVULKAN_MEMORYPART_HPP

#include "IMemoryPart.hpp"
#include <memory>
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace memory
			{
				class MemoryBlock;

				class MemoryPart :
					public virtual IMemoryPart
				{
				public:
					MemoryPart(std::shared_ptr<MemoryBlock> block, VkDeviceSize offset, VkDeviceSize size);
					~MemoryPart();
					std::shared_ptr<vulkan::Memory> getMemory() const override;
					VkDeviceSize getOffset() const override;
					VkDeviceSize getSize() const override;
					std::shared_ptr<const IMemoryBlock> getBlock() const override;
				private:
					const std::shared_ptr<MemoryBlock> block_;
					const VkDeviceSize offset_;
					const VkDeviceSize size_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_MEMORYPART_HPP
