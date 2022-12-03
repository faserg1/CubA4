#pragma once

#include <memory>
#include <vulkan/Device.hpp>
#include <vulkan/Memory.hpp>
#include <vulkan/vulkan.h>

namespace CubA4::render::engine
{
	namespace memory
	{
		enum class MemoryAllocationPrefered
		{
			Device,
			Host
		};

		class MemoryAllocator
		{
		public:
			explicit MemoryAllocator(std::shared_ptr<const vulkan::Device> device);
			~MemoryAllocator();

			std::shared_ptr<vulkan::Memory> allocate(size_t size, MemoryAllocationPrefered preference, uint32_t supportedTypes);
			std::shared_ptr<vulkan::Memory> allocateAndBind(VkBuffer buffer, MemoryAllocationPrefered preference);
			std::shared_ptr<vulkan::Memory> allocateAndBind(VkImage image, MemoryAllocationPrefered preference);
		protected:
		private:
			const std::shared_ptr<const vulkan::Device> device_;
		};
	}
}

