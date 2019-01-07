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

				vulkan::sVkDescriptorSetLayout getWorldLayout() const;
				vulkan::sVkDescriptorSetLayout getChunkLayout() const;
				vulkan::sVkDescriptorPool getBuiltInPool() const;
			protected:
			private:
				const std::shared_ptr<const vulkan::Device> device_;
				vulkan::sVkDescriptorSetLayout worldLayout_;
				vulkan::sVkDescriptorSetLayout chunkLayout_;
				vulkan::sVkDescriptorPool builtInPool_;
			private:
				void createBuildInDescriptorSetLayouts();
				void createBuiltInDescriptorPool();

				vulkan::sVkDescriptorSetLayout createSetFromBindings(const VkDescriptorSetLayoutBinding *bindings, size_t count, const char *name);
			};
		}
	}
}

#endif // RENDERVULKAN_RESOURCEMANAGER_HPP
