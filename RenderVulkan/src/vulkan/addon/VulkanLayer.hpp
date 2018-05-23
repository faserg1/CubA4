#ifndef VULKANLAYER_HPP
#define VULKANLAYER_HPP

#include "VulkanInstanceAddon.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class VulkanLayer :
					public VulkanInstanceAddon
				{
				public:
					explicit VulkanLayer();
					~VulkanLayer();
				protected:
				private:
				};
			}
		}
	}
}

#endif // VULKANLAYER_HPP
