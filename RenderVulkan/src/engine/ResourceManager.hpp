#ifndef RENDERVULKAN_RESOURCEMANAGER_HPP
#define RENDERVULKAN_RESOURCEMANAGER_HPP

#include <memory>
#include <vulkan/vulkan.h>
#include "../vulkan/util/VulkanHandlerContainer.hpp"

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

				vulkan::sVkDescriptorSetLayout getBuiltInLayout() const;
			protected:
			private:
				const std::shared_ptr<const vulkan::Device> device_;
				vulkan::sVkDescriptorSetLayout builtInLayout_;
				VkDescriptorPool builtInPool_;
			private:
				void createBuildInDescriptorSetLayout();
				void destroyBuildInDescriptorSetLayout();

				void createBuiltInDescriptorPool();
				void destroyBuiltInDescriptorPool();
			};
		}
	}
}

#endif // RENDERVULKAN_RESOURCEMANAGER_HPP
