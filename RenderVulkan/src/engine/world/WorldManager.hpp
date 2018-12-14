#ifndef RENDERVULKAN_WORLDMANAGER_HPP
#define RENDERVULKAN_WORLDMANAGER_HPP

#include <memory>
#include <engine/world/IWorldManager.hpp>
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
			class ResourceManager;

			namespace world
			{
				class WorldManager :
					public virtual IWorldManager
				{
				public:
					explicit WorldManager(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<ResourceManager> resourceManager);
					~WorldManager();

					void setCameraPosition(double x, double y, double z) override;
					/**
					\param roll Вращение вокруг оси x
					\param pitch Вращение вокруг оси y
					\param yaw Вращение вокруг оси z
					**/
					void setCameraRotation(double roll, double pitch, double yaw) override;
					void setFieldOfView(float degrees) override;

					vulkan::sVkDescriptorSet getWorldDescriptorSetLayout() const;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<ResourceManager> resourceManager_;

					vulkan::sVkDescriptorPool pool_;
					vulkan::sVkDescriptorSetLayout layout_;
					vulkan::sVkDescriptorSet worldSet_;
				private:
					void allocateSets();
				};
			}
		}
	}
}

#endif // RENDERVULKAN_WORLDMANAGER_HPP
