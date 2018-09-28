#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <memory>
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
		}

		namespace engine
		{
			class ResourceManager
			{
			public:
				explicit ResourceManager(std::shared_ptr<const vulkan::Device> device);
				~ResourceManager();

				VkDescriptorSetLayout getBuiltInLayout() const;
			protected:
			private:
				const std::shared_ptr<const vulkan::Device> device_;
				VkDescriptorSetLayout builtInLayout_;
			private:
				void createBuildInDescriptorSetLayout();
				void destroyBuildInDescriptorSetLayout();
			};
		}
	}
}

#endif // RESOURCEMANAGER_HPP
