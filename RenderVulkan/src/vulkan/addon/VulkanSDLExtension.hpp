#ifndef VULKANSDLEXTENSION_HPP
#define VULKANSDLEXTENSION_HPP

#include <memory>
#include "VulkanExtension.hpp"

namespace CubA4
{
	namespace window
	{
		class IWindow;
	}

	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class VulkanSDLExtension :
					public VulkanExtension
				{
				public:
					explicit VulkanSDLExtension(std::shared_ptr<window::IWindow> window);
					~VulkanSDLExtension();

					std::vector<std::string> names() const override;
					void init(std::shared_ptr<const VulkanInstance> instance) override;
					void destroy(std::shared_ptr<const VulkanInstance> instance) override;
				protected:
				private:
					std::shared_ptr<window::IWindow> window_;
				};
			}
		}
	}
}

#endif // VULKANSDLEXTENSION_HPP
