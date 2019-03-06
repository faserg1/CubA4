#ifndef RENDERVULKAN_MATERIALLAYOUT_HPP
#define RENDERVULKAN_MATERIALLAYOUT_HPP

#include <memory>
#include <engine/material/IMaterialLayout.hpp>
#include <vulkan/vulkan.h>
#include "../../vulkan/util/VulkanHandlerContainer.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Pipeline;
		}

		namespace engine
		{
			namespace material
			{
				class MaterialLayout :
					virtual public IMaterialLayout
				{
				public:
					explicit MaterialLayout(std::shared_ptr<vulkan::Pipeline> pipeline, vulkan::sVkDescriptorSetLayout textureLayout);
					~MaterialLayout();

					std::shared_ptr<vulkan::Pipeline> getPipeline() const;
					vulkan::sVkDescriptorSetLayout getLayout() const;
				protected:
				private:
					const std::shared_ptr<vulkan::Pipeline> pipeline_;
					const vulkan::sVkDescriptorSetLayout textureLayout_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_MATERIALLAYOUT_HPP
