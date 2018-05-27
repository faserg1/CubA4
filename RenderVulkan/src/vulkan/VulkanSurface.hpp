#ifndef VULKANSURFACE_HPP
#define VULKANSURFACE_HPP

#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanSurface
			{
			public:
				explicit VulkanSurface(VkSurfaceKHR surafece);
				~VulkanSurface();

				VkSurfaceKHR getSurface() const;
			protected:
			private:
				const VkSurfaceKHR surface_;
			};
		}
	}
}

#endif // VULKANSURFACE_HPP
