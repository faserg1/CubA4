#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <resources/IResource.hpp>
#include <ICore.hpp>
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
				explicit ResourceManager(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<const ICore> core);
				~ResourceManager();


				// TODO: extract built ins in another class?
				vulkan::sVkDescriptorSetLayout getWorldLayout() const;
				std::vector<vulkan::sVkDescriptorSetLayout> getBuiltInLayouts() const;
				vulkan::sVkDescriptorPool getBuiltInPool() const;

				std::shared_ptr<resources::IResource> getCache(resources::Path path) const;
			protected:
			private:
				const std::shared_ptr<const vulkan::Device> device_;
				std::shared_ptr<const ICore> core_;
				vulkan::sVkDescriptorSetLayout worldLayout_;
				vulkan::sVkDescriptorPool builtInPool_;
			private:
				void createBuildInDescriptorSetLayouts();
				void createBuiltInDescriptorPool();

				vulkan::sVkDescriptorSetLayout createSetFromBindings(const VkDescriptorSetLayoutBinding *bindings, size_t count, const char *name);
			};
		}
	}
}
