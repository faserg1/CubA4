#ifndef VULKANSTANDARTVALIDATIONLAYER_HPP
#define VULKANSTANDARTVALIDATIONLAYER_HPP

#include "InstanceLayer.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class VulkanStandardValidationLayer :
					public VulkanInstanceLayer
				{
				public:
					explicit VulkanStandardValidationLayer();
					~VulkanStandardValidationLayer();

					std::vector<std::string> names() const override;
					void init(std::shared_ptr<const VulkanInstance> instance) override;
					void destroy(std::shared_ptr<const VulkanInstance> instance) override;
					void added(VulkanInstanceBuilder &builder) override;
				protected:
				private:
				};
			}
		}
	}
}

#endif // VULKANSTANDARTVALIDATIONLAYER_HPP
