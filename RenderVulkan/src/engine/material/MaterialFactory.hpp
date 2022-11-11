#pragma once

#include <memory>
#include <engine/material/IMaterialFactory.hpp>
#include <engine/material/DescriptorPool.hpp>
#include <vulkan/vulkan.h>
#include "../../vulkan/util/VulkanHandlerContainer.hpp"

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
			namespace material
			{
				class MaterialFactory :
					public virtual IMaterialFactory
				{
				public:
					explicit MaterialFactory(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<const DescriptorPool> pool);
					~MaterialFactory();

					std::shared_ptr<IMaterialBuilder> createMaterial(std::shared_ptr<const IMaterialLayout> layout) override;
				protected:
					void createSampler();
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<const DescriptorPool> pool_;
					VkSampler sampler_;
				};
			}
		}
	}
}
