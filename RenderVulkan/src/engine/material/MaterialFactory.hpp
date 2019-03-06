#ifndef RENDERVULKAN_MATERIALFACTORY_HPP
#define RENDERVULKAN_MATERIALFACTORY_HPP

#include <memory>
#include <engine/material/IMaterialFactory.hpp>
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
					explicit MaterialFactory(std::shared_ptr<const vulkan::Device> device);
					~MaterialFactory();

					std::shared_ptr<IMaterialBuilder> createMaterial(std::shared_ptr<const IMaterialLayout> layout) override;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					vulkan::sVkDescriptorPool pool_;
				private:
					void createDescriptorPool();
				};
			}
		}
	}
}

#endif // RENDERVULKAN_MATERIALFACTORY_HPP
