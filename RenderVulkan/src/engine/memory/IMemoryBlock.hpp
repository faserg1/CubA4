#pragma once

#include <vulkan/vulkan.h>
#include <cstdint>

namespace CubA4::render::engine::memory
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
