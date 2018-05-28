#ifndef VULKANSWAPCHAINEXTENSION_HPP
#define VULKANSWAPCHAINEXTENSION_HPP

#include "VulkanDeviceExtension.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class VulkanSwapchainExtension :
					public VulkanDeviceExtension
				{
				public:
					explicit VulkanSwapchainExtension();
					~VulkanSwapchainExtension();

					std::vector<std::string> names() const override;
				protected:
				private:
				};
			}
		}
	}
}

#endif // VULKANSWAPCHAINEXTENSION_HPP
