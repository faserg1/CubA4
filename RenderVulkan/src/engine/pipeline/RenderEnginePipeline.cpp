#include <engine/pipeline/RenderEnginePipeline.hpp>
#include <engine/pipeline/RenderChunkCompiler.hpp>
using namespace CubA4::render::engine::pipeline;

RenderEnginePipeline::RenderEnginePipeline(std::shared_ptr<const ICore> core, std::shared_ptr<const vulkan::Device> device,
	std::shared_ptr<const engine::RenderPassManager> renderPassManager, std::shared_ptr<engine::RenderManager> renderManager) :
	core_(core), device_(device), renderPassManager_(renderPassManager), renderManager_(renderManager)
{
	auto chunkCompiler = std::make_shared<pipeline::RenderChunkCompiler>(core_, device,
		renderPassManager->getMainRenderPass(), renderManager_, renderPassManager->getMainInfo().worldSubpass);
	// TODO: ?
	worldPipeline_ = std::make_shared<pipeline::RenderEngineWorldPipeline>(chunkCompiler, RenderFramebufferData{});
}

void RenderEnginePipeline::onFramebufferUpdated(const RenderFramebufferData &data)
{
	worldPipeline_->onFramebufferUpdated(data);
}

std::shared_ptr<RenderEngineWorldPipeline> RenderEnginePipeline::getWorldPipeline() const
{
	return worldPipeline_;
}