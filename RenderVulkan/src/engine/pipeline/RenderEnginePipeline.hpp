#pragma once

#include <ICore.hpp>
#include <vulkan/Device.hpp>
#include <engine/pipeline/IRenderEnginePipeline.hpp>
#include <engine/pipeline/RenderEngineWorldPipeline.hpp>
#include <engine/RenderPassManager.hpp>
#include <engine/RenderManager.hpp>
#include <memory>

namespace CubA4::render::engine::pipeline
{
	class RenderEnginePipeline : public virtual IRenderEnginePipeline
	{
	public:
		RenderEnginePipeline(std::shared_ptr<const ICore> core, std::shared_ptr<const vulkan::Device> device,
			std::shared_ptr<const engine::RenderPassManager> renderPassManager, std::shared_ptr<engine::RenderManager> renderManager);
		~RenderEnginePipeline() = default;

		void setup(const RenderFramebufferData &data); // todo

		void onFramebufferUpdated(const RenderFramebufferData &data) override;
		std::shared_ptr<RenderEngineWorldPipeline> getWorldPipeline() const;
	private:
		const std::shared_ptr<const ICore> core_;
		const std::shared_ptr<const vulkan::Device> device_;
		const std::shared_ptr<const engine::RenderPassManager> renderPassManager_;
		const std::shared_ptr<RenderManager> renderManager_;
		
		std::shared_ptr<RenderEngineWorldPipeline> worldPipeline_;
	};
}
