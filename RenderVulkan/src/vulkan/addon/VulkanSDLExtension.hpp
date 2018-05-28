#ifndef VULKANSDLEXTENSION_HPP
#define VULKANSDLEXTENSION_HPP

#include <memory>
#include "VulkanInstanceExtension.hpp"

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
			class VulkanSurface;

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

					std::shared_ptr<const VulkanSurface> getSurface() const;
				protected:
				private:
					std::shared_ptr<window::IWindow> window_;
					std::shared_ptr<VulkanSurface> surface_;
				};
			}
		}
	}
}

#endif // VULKANSDLEXTENSION_HPP
