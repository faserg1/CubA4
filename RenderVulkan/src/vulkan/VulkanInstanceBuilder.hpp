#ifndef VULKANINSTANCEBUILDER_HPP
#define VULKANINSTANCEBUILDER_HPP

#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace layer
			{
				class VulkanLayer;
			}

			class VulkanInstance;
			struct VulkanInstanceBuilderData;

			class VulkanInstanceBuilder
			{
				std::shared_ptr<VulkanInstanceBuilderData> data_;
			public:
				explicit VulkanInstanceBuilder();
				~VulkanInstanceBuilder();

				std::shared_ptr<const VulkanInstance> build();
			protected:
			private:
				void fillAppInfo();
				
			};
		}
	}
}

#endif // VULKANINSTANCEBUILDER_HPP
