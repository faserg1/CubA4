#ifndef IVULKANINSTANCEADDON_HPP
#define IVULKANINSTANCEADDON_HPP

#include <string>
#include <vector>
#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanInstance;
			
			namespace addon
			{
				class IVulkanInstanceAddon
				{
				public:
					virtual ~IVulkanInstanceAddon() {}
					
					virtual std::vector<std::string> names() const = 0;
					virtual void init(std::shared_ptr<VulkanInstance> instance) = 0;
					virtual void destroy(std::shared_ptr<VulkanInstance> instance) = 0;
				protected:
					explicit IVulkanInstanceAddon() {}
				private:
				};
			}
		}
	}
}

#endif // IVULKANINSTANCEADDON_HPP
