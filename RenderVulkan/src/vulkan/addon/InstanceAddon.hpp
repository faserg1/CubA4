#ifndef IVULKANINSTANCEADDON_HPP
#define IVULKANINSTANCEADDON_HPP

#include <memory>
#include "Addon.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanInstance;
			class VulkanInstanceBuilder;
			
			namespace addon
			{
				class VulkanInstanceAddon :
					public VulkanAddon
				{
				public:
					VulkanAddonType type() const override;
					virtual void init(std::shared_ptr<const VulkanInstance> instance) = 0;
					virtual void destroy(std::shared_ptr<const VulkanInstance> instance) = 0;
					virtual void added(VulkanInstanceBuilder &builder) = 0;
				protected:
					explicit VulkanInstanceAddon();
					virtual ~VulkanInstanceAddon();
				private:
				};
			}
		}
	}
}

#endif // IVULKANINSTANCEADDON_HPP
