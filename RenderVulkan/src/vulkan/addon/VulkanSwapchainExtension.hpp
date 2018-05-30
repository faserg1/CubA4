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
					explicit VulkanSwapchainExtension(std::weak_ptr<VulkanPhysicalDevice> physicalDevice);
					~VulkanSwapchainExtension();

					std::vector<std::string> names() const override;
					void init(std::shared_ptr<const VulkanDevice> instance) override;
					void destroy(std::shared_ptr<const VulkanDevice> instance) override;
					void added(VulkanDeviceBuilder &builder) override;
				protected:
				private:
				};
			}
		}
	}
}

#endif // VULKANSWAPCHAINEXTENSION_HPP
