#pragma once

#include <vulkan/vulkan.h>

namespace CubA4::render::vulkan
{
	class Instance 
	{
	public:
		explicit Instance(VkInstance instance, uint32_t apiVersion);
		~Instance();
		VkInstance getInstance() const;
		uint32_t getAPIVersion() const;
	protected:
		
	private:
		const VkInstance instance_;
		const uint32_t apiVersion_;
	};
}
