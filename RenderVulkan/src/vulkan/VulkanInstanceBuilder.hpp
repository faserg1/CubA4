#ifndef VULKANINSTANCEBUILDER_HPP
#define VULKANINSTANCEBUILDER_HPP

#include <memory>
#include <string>
#include <vector>

namespace CubA4
{
	namespace core
	{
		namespace info
		{
			class IApplicationInfo;
		}
	}

	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class VulkanInstanceLayer;
				class VulkanExtension;
			}

			class VulkanInstance;
			struct VulkanInstanceBuilderData;

			class VulkanInstanceBuilder
			{
				std::shared_ptr<VulkanInstanceBuilderData> data_;
			public:
				explicit VulkanInstanceBuilder(std::shared_ptr<const core::info::IApplicationInfo> info);
				~VulkanInstanceBuilder();

				void addLayer(addon::VulkanInstanceLayer &layer);
				void addExtension(addon::VulkanExtension &extension);
				std::shared_ptr<const VulkanInstance> build();
				void destroy(std::shared_ptr<const VulkanInstance> instance);
			protected:
			private:
				void fillAppInfo();
				
				std::shared_ptr<const core::info::IApplicationInfo> info_;
				std::vector<std::string> extensions_;
				std::vector<std::string> layers_;
			};
		}
	}
}

#endif // VULKANINSTANCEBUILDER_HPP
