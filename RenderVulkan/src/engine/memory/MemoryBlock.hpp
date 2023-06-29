#pragma once

#include <memory>
#include <list>
#include "IMemoryBlock.hpp"

namespace CubA4::render
{
	namespace vulkan
	{
		class Memory;
	}

	namespace engine::memory
	{
		class MemoryPart;

		class MemoryBlock :
			public std::enable_shared_from_this<MemoryBlock>,
			public virtual IMemoryBlock
		{
		public:
			MemoryBlock(std::shared_ptr<vulkan::Memory> memory);
			VkMemoryPropertyFlags getFlags() const override;
			uint32_t getMemoryTypeIndex() const override;
			std::shared_ptr<vulkan::Memory> getMemory() const;
			std::shared_ptr<MemoryPart> allocatePart(uint64_t size, uint64_t alignment);
			void freePart(const MemoryPart *part);
		private:
			std::shared_ptr<vulkan::Memory> memory_;
			std::list<std::weak_ptr<MemoryPart>> parts_;
		};
	}
}

