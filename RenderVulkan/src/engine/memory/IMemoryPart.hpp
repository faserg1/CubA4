#pragma once


#include <memory>
#include <vulkan/vulkan.h>

namespace CubA4::render
{
	namespace vulkan
	{
		class Memory;
	}

	namespace engine::memory
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
