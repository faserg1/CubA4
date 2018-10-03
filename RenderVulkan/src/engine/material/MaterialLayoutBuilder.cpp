#include "./MaterialLayoutBuilder.hpp"
#include "../Render.hpp"
#include "../ResourceManager.hpp"
#include <stdexcept>
#include <algorithm>
#include "../../vulkan/RenderPass.hpp"
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialLayoutBuilder::MaterialLayoutBuilder(std::shared_ptr<const Device> device,
	std::shared_ptr<const Render> render, std::shared_ptr<const ResourceManager> resourceManager) :
	device_(device), render_(render), resourceManager_(resourceManager), pipelineBuilder_(device)
{
	pipelineBuilder_.addBuiltInDescriptorSetLayout(resourceManager->getBuiltInLayout());
}

MaterialLayoutBuilder::~MaterialLayoutBuilder()
{
	
}

void MaterialLayoutBuilder::useShader(std::shared_ptr<const IShader> shader)
{
	pipelineBuilder_.useShader(shader);
}

void MaterialLayoutBuilder::prepare(VkGraphicsPipelineCreateInfo &pipelineCreateInfo)
{
	pipelineCreateInfo = pipelineBuilder_.build();
	pipelineCreateInfo.renderPass = render_->getRenderPass()->getRenderPass();
}

void MaterialLayoutBuilder::fillPipelineInfo(PipelineInfo &pipelineInfo) const
{
	pipelineBuilder_.fillPipelineInfo(pipelineInfo);
}