#pragma once

#include <memory>
#include <engine/IRenderManager.hpp>
#include <ICore.hpp>
#include <vulkan/Instance.hpp>
#include <vulkan/Device.hpp>
#include <engine/RenderPassManager.hpp>
#include <engine/ResourceManager.hpp>
#include <engine/framebuffer/FramebufferManager.hpp>
#include <engine/model/ModelManager.hpp>
#include <engine/material/MaterialManager.hpp>
#include <engine/world/WorldManager.hpp>
#include <engine/debug/RenderDebug.hpp>
#include <ui/UIManager.hpp>

namespace CubA4::render::engine
{
	class RenderManager :
		public std::enable_shared_from_this<RenderManager>,
		public virtual IRenderManager
	{
	public:
		explicit RenderManager(std::shared_ptr<const vulkan::Instance> instance,
			std::shared_ptr<const vulkan::Device> device,
			std::shared_ptr<const ICore> core,
			std::shared_ptr<const RenderPassManager> rpManager,
			std::shared_ptr<const config::IRenderConfig> config);
		~RenderManager();

		void onRenderPassCreated();
		void setup();

		std::shared_ptr<material::IMaterialManager> getMaterialManager() const override;
		std::shared_ptr<model::IModelManager> getModelManager() const override;
		std::shared_ptr<model::ModelManager> getModelManager();
		std::shared_ptr<world::IWorldManager> getWorldManager() const override;
		std::shared_ptr<world::WorldManager> getWorldManager();
		std::shared_ptr<CubA4::render::ui::IRenderUIManager> getUIManager() const override;
		std::shared_ptr<CubA4::render::ui::UIManager> getUIManager();
		std::shared_ptr<debug::IRenderDebug> getDebug() const override;
		std::shared_ptr<debug::RenderDebug> getDebug();

		std::shared_ptr<ResourceManager> getResourceManager() const;
	protected:
	private:
		const std::shared_ptr<const vulkan::Instance> instance_;
		const std::shared_ptr<const vulkan::Device> device_;
		const std::shared_ptr<const ICore> core_;
		const std::shared_ptr<const RenderPassManager> rpManager_;
		const std::shared_ptr<const config::IRenderConfig> config_;
		std::shared_ptr<ResourceManager> resourceManager_;
		std::shared_ptr<material::MaterialManager> materialManager_;
		std::shared_ptr<model::ModelManager> modelManager_;
		std::shared_ptr<world::WorldManager> worldManager_;
		std::shared_ptr<CubA4::render::ui::UIManager> uiManager_;
		std::shared_ptr<CubA4::render::engine::debug::RenderDebug> debug_;
	};
}
