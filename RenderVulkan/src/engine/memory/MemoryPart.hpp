#pragma once

#include "IMemoryPart.hpp"
#include <memory>
#include <vulkan/vulkan.h>

namespace CubA4::render::engine::memory
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
		std::shared_ptr<void> map(VkDeviceSize offset, VkDeviceSize size) const override;
		void flush(VkDeviceSize offset, VkDeviceSize size) const override;
	private:
		const std::shared_ptr<MemoryBlock> block_;
		const VkDeviceSize offset_;
		const VkDeviceSize size_;
	};
}
