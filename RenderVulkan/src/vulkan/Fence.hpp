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
		explicit Fence(std::shared_ptr<const Device> device, VkFenceCreateFlags flags);
		~Fence();

		VkFence getFence() const;
	private:
		std::shared_ptr<const Device> device_;
		VkFence fence_;
	};
}
