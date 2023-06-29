#include "./MaterialLayoutBuilder.hpp"
#include "./ShaderFactory.hpp"
#include "../Render.hpp"
#include "../ResourceManager.hpp"
#include <stdexcept>
#include <algorithm>
#include "../../vulkan/RenderPass.hpp"

#include "../../../gen/irs.hpp"
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialLayoutBuilder::MaterialLayoutBuilder(std::shared_ptr<const Device> device,
	std::shared_ptr<const RenderPassManager> rpManager, std::shared_ptr<const ResourceManager> resourceManager,
	CubA4::render::config::VulkanConfigAdapter config) :
	device_(device), rpManager_(rpManager), resourceManager_(resourceManager), config_(config), pipelineBuilder_(device, config),
	shaderFactory_(std::make_unique<ShaderFactory>(device))
{
	for (auto layout : resourceManager->getBuiltInLayouts())
	{
		pipelineBuilder_.addBuiltInDescriptorSetLayout(layout);
	}
}

MaterialLayoutBuilder::~MaterialLayoutBuilder()
{
	
}

void MaterialLayoutBuilder::setType(MaterialType type)
{
	std::shared_ptr<const IShader> vertexShader, fragmentShader;

	const void *vertexShaderData, *fragmentShaderData;
	std::size_t vertexShaderSize, fragmentShaderSize;

	switch (type)
	{
	case CubA4::render::engine::material::MaterialType::Block:
		vertexShaderData = irs::findFile("shaders/block.vert.spv", vertexShaderSize);
		fragmentShaderData = irs::findFile("shaders/block.frag.spv", fragmentShaderSize);
		break;
	default:
		break;
	}

	if (!vertexShaderData || !fragmentShaderData)
	{
		// TODO: [OOKAMI] Logs, exceptions...
		return;
	}

	vertexShader = shaderFactory_->createFromBinary(vertexShaderData, vertexShaderSize, CubA4::render::engine::material::ShaderType::Vertex, "main");
	fragmentShader = shaderFactory_->createFromBinary(fragmentShaderData, fragmentShaderSize, CubA4::render::engine::material::ShaderType::Fragment, "main");

	pipelineBuilder_.useShader(vertexShader);
	pipelineBuilder_.useShader(fragmentShader);
}

void MaterialLayoutBuilder::addTexture()
{
	pipelineBuilder_.addTexture();
}

sVkDescriptorSetLayout MaterialLayoutBuilder::getTextureLayout()
{
	return pipelineBuilder_.getTextureLayout();
}

void MaterialLayoutBuilder::prepare(VkGraphicsPipelineCreateInfo &pipelineCreateInfo)
{
	pipelineCreateInfo = pipelineBuilder_.build();
	pipelineCreateInfo.renderPass = rpManager_->getMainRenderPass()->getRenderPass();
	pipelineCreateInfo.subpass = rpManager_->getMainInfo().worldSubpass;
}

void MaterialLayoutBuilder::fillPipelineInfo(PipelineInfo &pipelineInfo) const
{
	pipelineBuilder_.fillPipelineInfo(pipelineInfo);
}
