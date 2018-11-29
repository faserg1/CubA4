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

				std::shared_ptr<VkDescriptorSetLayout> getBuiltInLayout() const;
			protected:
			private:
				const std::shared_ptr<const vulkan::Device> device_;
				std::shared_ptr<VkDescriptorSetLayout> builtInLayout_;
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

#endif // RESOURCEMANAGER_HPP
