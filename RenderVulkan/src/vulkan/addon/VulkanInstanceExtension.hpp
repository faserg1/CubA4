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
				struct VulkanExtensionPrivate;

				class VulkanExtension :
					public VulkanInstanceAddon
				{
				public:
					
					~VulkanExtension();
				protected:
					explicit VulkanExtension();
					std::vector<std::string> allNames() const override;
				private:
					std::shared_ptr<VulkanExtensionPrivate> data_;
				};
			}
		}
	}
}

#endif // VULKANEXTENSION_HPP
