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
				class VulkanInstanceAddon
				{
				public:
					virtual ~VulkanInstanceAddon() {}
					
					virtual std::vector<std::string> names() const = 0;
					virtual void init(std::shared_ptr<VulkanInstance> instance) = 0;
					virtual void destroy(std::shared_ptr<VulkanInstance> instance) = 0;

					bool available() const;
				protected:
					virtual std::vector<std::string> allNames() const = 0;
					explicit VulkanInstanceAddon() {}
				private:
				};
			}
		}
	}
}

#endif // IVULKANINSTANCEADDON_HPP
