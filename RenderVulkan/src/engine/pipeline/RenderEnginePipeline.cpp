#include <engine/pipeline/RenderEnginePipeline.hpp>
#include <engine/compilers/RenderChunkCompiler.hpp>
#include <engine/compilers/RenderEntityCompiler.hpp>
using namespace CubA4::render::engine::pipeline;

RenderEnginePipeline::RenderEnginePipeline(std::shared_ptr<const ICore> core, std::shared_ptr<const vulkan::Device> device,
	std::shared_ptr<const engine::RenderPassManager> renderPassManager, std::shared_ptr<engine::RenderManager> renderManager) :
	core_(core), device_(device), renderPassManager_(renderPassManager), renderManager_(renderManager)
{
	auto mainRenderPass = renderPassManager->getMainRenderPass();
	auto worldSubpass = renderPassManager->getMainInfo().worldSubpass;

	auto chunkCompiler = std::make_shared<pipeline::RenderChunkCompiler>(core_, device,
		mainRenderPass, renderManager_, worldSubpass);
	auto entityCompiler = std::make_shared<pipeline::RenderEntityCompiler>(core_, device,
		mainRenderPass, renderManager_, worldSubpass);
	
	worldPipeline_ = std::make_shared<pipeline::RenderEngineWorldPipeline>(chunkCompiler);
	entityPipeline_ = std::make_shared<pipeline::RenderEntityPipeline>(entityCompiler);
}

void RenderEnginePipeline::onFramebufferUpdated(const RenderFramebufferData &data)
{
	worldPipeline_->onFramebufferUpdated(data);
	entityPipeline_->onFramebufferUpdated(data);
}

std::shared_ptr<RenderEngineWorldPipeline> RenderEnginePipeline::getWorldPipeline() const
{
	return worldPipeline_;
}

std::shared_ptr<RenderEntityPipeline> RenderEnginePipeline::getEntityPipeline() const
{
	return entityPipeline_;
}