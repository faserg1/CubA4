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

			namespace memory
			{
				class MemoryAllocator;
				class MemoryManager;
				class MemoryHelper;
			}
			

			namespace world
			{
				class WorldManager :
					public virtual IWorldManager
				{
				public:
					explicit WorldManager(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<ResourceManager> resourceManager);
					~WorldManager();

					void setCameraPosition(CubA4::mod::world::ChunkPos globalPos, float x, float y, float z) override;
					/**
					\param roll Вращение вокруг оси x
					\param pitch Вращение вокруг оси y
					\param yaw Вращение вокруг оси z
					**/
					void setCameraRotation(float roll, float pitch, float yaw) override;
					void setFieldOfView(float degrees) override;

					vulkan::sVkDescriptorSet getWorldDescriptorSet() const;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<ResourceManager> resourceManager_;
					const std::shared_ptr<memory::MemoryAllocator> memoryAllocator_;
					const std::shared_ptr<memory::MemoryManager> memoryManager_;
					const std::shared_ptr<memory::MemoryHelper> memoryHelper_;

					vulkan::sVkDescriptorPool pool_;
					vulkan::sVkDescriptorSetLayout layout_;
					vulkan::sVkDescriptorSet worldSet_;
					vulkan::sVkBuffer worldBuffer_;

					struct
					{
						CubA4::mod::world::ChunkPos viewGlobalPos;
						float viewX;
						float viewY;
						float viewZ;

						float viewRoll;
						float viewPitch;
						float viewYaw;

						float projectionFov;
						float projectionAspect;
					} worldData_;
				private:
					void allocateSets();
					void allocateBuffers();
					void writeSets();

					void updateViewMatrix();
					void updateProjectionMatrix();
				};
			}
		}
	}
}

#endif // RENDERVULKAN_WORLDMANAGER_HPP
