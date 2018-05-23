#ifndef VULKANDEBUGEXTENSION_HPP
#define VULKANDEBUGEXTENSION_HPP

#include "VulkanExtension.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class VulkanDebugExtension :
					public VulkanExtension
				{
				public:
					explicit VulkanDebugExtension();
					~VulkanDebugExtension();

					std::vector<std::string> names() const;
					void init(std::shared_ptr<VulkanInstance> instance);
					void destroy(std::shared_ptr<VulkanInstance> instance);
				protected:
				private:
				};
			}
		}
	}
}

#endif // VULKANDEBUGEXTENSION_HPP
