#ifndef VULKANINSTANCE_HPP
#define VULKANINSTANCE_HPP

#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanInstance
			{
			public:
				explicit VulkanInstance(VkInstance instance);
				~VulkanInstance();
				VkInstance get() const;
			protected:
				
			private:
				const VkInstance instance_;
			};
		}
	}
}

#endif // VULKANINSTANCE_HPP
