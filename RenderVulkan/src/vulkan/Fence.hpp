#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <vulkan/Device.hpp>

namespace CubA4::render::vulkan
{
	class Fence :
		public std::enable_shared_from_this<Fence>
	{
	public:
		explicit Fence(std::shared_ptr<const Device> device, VkFenceCreateFlags flags = 0);
		Fence(const Fence &old) = delete;
		// move ctr?
		~Fence();

		VkFence getFence() const;
		VkResult wait(uint64_t timeout = VK_WHOLE_SIZE);
		void reset();
	private:
		std::shared_ptr<const Device> device_;
		VkFence fence_;
	};
}
