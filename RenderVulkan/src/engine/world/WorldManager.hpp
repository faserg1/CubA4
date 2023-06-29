#pragma once

#include <memory>
#include <engine/world/IWorldManager.hpp>
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include "../../vulkan/util/VulkanHandlerContainer.hpp"

namespace CubA4::render
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
			class Camera;

			class WorldManager :
				public virtual IWorldManager
			{
			public:
				explicit WorldManager(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<ResourceManager> resourceManager);
				~WorldManager();

				std::shared_ptr<ICamera> createCamera() override;
				void setActiveCamera(std::shared_ptr<ICamera> camera) override;
				void setFieldOfView(float degrees) override;

				Ray getRayFrom(uint64_t x, uint64_t y, std::shared_ptr<const ICamera> camera = {}) const override;

				void onViewportUpdate(uint64_t width, uint64_t height);
				void onFrameUpdate();
				vulkan::sVkDescriptorSet getWorldDescriptorSet() const;
			protected:
				const std::shared_ptr<const vulkan::Device> device_;
				const std::shared_ptr<ResourceManager> resourceManager_;
				const std::shared_ptr<memory::MemoryAllocator> memoryAllocator_;
				const std::shared_ptr<memory::MemoryManager> memoryManager_;
				const std::shared_ptr<memory::MemoryHelper> memoryHelper_;

				std::weak_ptr<Camera> activeCamera_;
			private:
				vulkan::sVkDescriptorPool pool_;
				vulkan::sVkDescriptorSetLayout layout_;
				vulkan::sVkDescriptorSet worldSet_;
				vulkan::sVkBuffer worldBuffer_;

				struct
				{
					float projectionFov = 1;
					float projectionWidth = 1;
					float projectionHeight = 1;

					glm::mat4 projMatrix_ = {};
				} worldData_;
			private:
				void allocateSets();
				void allocateBuffers();
				void writeSets();
				
				void updateProjectionMatrix();
			};
		}
	}
}


