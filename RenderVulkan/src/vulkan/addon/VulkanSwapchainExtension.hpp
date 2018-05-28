#ifndef VULKANSWAPCHAINEXTENSION_HPP
#define VULKANSWAPCHAINEXTENSION_HPP

#include "VulkanInstanceExtension.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class VulkanSwapchainExtension :
					public VulkanExtension
				{
				public:
					explicit VulkanSwapchainExtension();
					~VulkanSwapchainExtension();

					std::vector<std::string> names() const override;
					void init(std::shared_ptr<const VulkanInstance> instance) override;
					void destroy(std::shared_ptr<const VulkanInstance> instance) override;
				protected:
				private:
				};
			}
		}
	}
}

#endif // VULKANSWAPCHAINEXTENSION_HPP
