#ifndef RENDERVULKAN_RENDERMANAGER_HPP
#define RENDERVULKAN_RENDERMANAGER_HPP

#include <memory>
#include <engine/IRenderManager.hpp>

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
			class Render;
			class ResourceManager;

			namespace material
			{
				class MaterialManager;
			}

			namespace model
			{
				class ModelManager;
			}

			namespace world
			{
				class WorldManager;
			}

			class RenderManager :
				public virtual IRenderManager
			{
			public:
				explicit RenderManager(std::shared_ptr<const vulkan::Device> device,
					std::shared_ptr<const Render> render);
				~RenderManager();

				std::shared_ptr<material::IMaterialManager> getMaterialManager() const override;
				std::shared_ptr<model::IModelManager> getModelManager() const override;
				std::shared_ptr<world::IWorldManager> getWorldManager() const override;

				std::shared_ptr<ResourceManager> getResourceManager() const;
			protected:
			private:
				const std::shared_ptr<const vulkan::Device> device_;
				const std::shared_ptr<const Render> render_;
				std::shared_ptr<ResourceManager> resourceManager_;
				std::shared_ptr<material::MaterialManager> materialManager_;
				std::shared_ptr<model::ModelManager> modelManager_;
				std::shared_ptr<world::WorldManager> worldManager_;
			};
		}
	}
}

#endif // RENDERVULKAN_RENDERMANAGER_HPP
