#include "./MaterialLayoutBuilder.hpp"
#include "../Render.hpp"
#include <stdexcept>
#include <algorithm>
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialLayoutBuilder::MaterialLayoutBuilder(std::shared_ptr<const Device> device, std::shared_ptr<const Render> render) :
	device_(device), render_(render), pipelineBuilder_(device)
{
	
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
	pipelineCreateInfo.renderPass = render_->getRenderPass();
}

void MaterialLayoutBuilder::fillPipelineInfo(PipelineInfo &pipelineInfo) const
{
	pipelineBuilder_.fillPipelineInfo(pipelineInfo);
}