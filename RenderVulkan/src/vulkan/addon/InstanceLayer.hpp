#ifndef VULKANLAYER_HPP
#define VULKANLAYER_HPP

#include "InstanceAddon.hpp"
#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				struct VulkanInstanceLayerData;

				class VulkanInstanceLayer :
					public VulkanInstanceAddon
				{
				public:
					explicit VulkanInstanceLayer();
					~VulkanInstanceLayer();
				protected:
					std::vector<std::string> allNames() const override;
				private:
					std::shared_ptr<VulkanInstanceLayerData> data_;
				};
			}
		}
	}
}

#endif // VULKANLAYER_HPP
