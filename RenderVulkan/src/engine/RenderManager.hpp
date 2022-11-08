#pragma once

#include <memory>
#include <engine/IRenderManager.hpp>
#include <ICore.hpp>
#include <vulkan/Device.hpp>
#include <engine/Render.hpp>
#include <engine/ResourceManager.hpp>
#include <engine/model/ModelManager.hpp>
#include <engine/material/MaterialManager.hpp>
#include <engine/world/WorldManager.hpp>

namespace CubA4::render::engine
{


	class RenderManager :
		public virtual IRenderManager
	{
	public:
		explicit RenderManager(std::shared_ptr<const vulkan::Device> device,
			std::shared_ptr<const ICore> core,
			std::shared_ptr<const Render> render);
		~RenderManager();

		std::shared_ptr<material::IMaterialManager> getMaterialManager() const override;
		std::shared_ptr<model::IModelManager> getModelManager() const override;
		std::shared_ptr<model::ModelManager> getModelManager();
		std::shared_ptr<world::IWorldManager> getWorldManager() const override;

		std::shared_ptr<ResourceManager> getResourceManager() const;
	protected:
	private:
		const std::shared_ptr<const vulkan::Device> device_;
		const std::shared_ptr<const ICore> core_;
		const std::shared_ptr<const Render> render_;
		std::shared_ptr<ResourceManager> resourceManager_;
		std::shared_ptr<material::MaterialManager> materialManager_;
		std::shared_ptr<model::ModelManager> modelManager_;
		std::shared_ptr<world::WorldManager> worldManager_;
	};
}
