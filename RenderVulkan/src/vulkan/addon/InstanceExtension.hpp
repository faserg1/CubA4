#ifndef VULKANEXTENSION_HPP
#define VULKANEXTENSION_HPP

#include "VulkanInstanceAddon.hpp"
#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				struct VulkanInstanceExtensionData;

				class VulkanInstanceExtension :
					public VulkanInstanceAddon
				{
				public:
					
					~VulkanInstanceExtension();
				protected:
					explicit VulkanInstanceExtension();
					std::vector<std::string> allNames() const override;
				private:
					std::shared_ptr<VulkanInstanceExtensionData> data_;
				};
			}
		}
	}
}

#endif // VULKANEXTENSION_HPP
