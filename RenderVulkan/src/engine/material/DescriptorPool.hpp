#pragma once

#include <vulkan/Device.hpp>
#include <vector>

namespace CubA4::render::engine::material
{
	class DescriptorPool
	{
	public:
		explicit DescriptorPool(std::shared_ptr<const vulkan::Device> device);
		~DescriptorPool();

		VkDescriptorPool get() const;
	protected:
		void createPool();
		virtual uint32_t getMaxSetCount() const = 0;
		virtual std::vector<VkDescriptorPoolSize> getPoolSizes() const = 0;
	private:
		
	private:
		std::shared_ptr<const vulkan::Device> device_;
		VkDescriptorPool pool_;
	};
}
