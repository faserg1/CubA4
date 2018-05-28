#ifndef VULKANLAYER_HPP
#define VULKANLAYER_HPP

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
				struct VulkanLayerPrivate;

				class VulkanInstanceLayer :
					public VulkanInstanceAddon
				{
				public:
					explicit VulkanInstanceLayer();
					~VulkanInstanceLayer();
				protected:
					std::vector<std::string> allNames() const override;
				private:
					std::shared_ptr<VulkanLayerPrivate> data_;
				};
			}
		}
	}
}

#endif // VULKANLAYER_HPP
