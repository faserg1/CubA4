#pragma once

#include <vulkan/vulkan.h>

namespace CubA4::render::vulkan
{
	class Instance 
	{
	public:
		explicit Instance(VkInstance instance);
		~Instance();
		VkInstance getInstance() const;
	protected:
		
	private:
		const VkInstance instance_;
	};
}
