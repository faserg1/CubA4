#ifndef SWAPCHAINEXTENSION_HPP
#define SWAPCHAINEXTENSION_HPP

#include "DeviceExtension.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class SwapchainExtension :
					public DeviceExtension
				{
				public:
					explicit SwapchainExtension(std::weak_ptr<PhysicalDevice> physicalDevice);
					~SwapchainExtension();

					std::vector<std::string> names() const override;
					void init(std::shared_ptr<const Device> instance) override;
					void destroy(std::shared_ptr<const Device> instance) override;
					void added(DeviceBuilder &builder) override;
				protected:
				private:
				};
			}
		}
	}
}

#endif // SWAPCHAINEXTENSION_HPP
