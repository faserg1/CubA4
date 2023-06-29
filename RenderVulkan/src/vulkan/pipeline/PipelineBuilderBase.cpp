#include <vulkan/pipeline/PipelineBuilderBase.hpp>
#include <vulkan/pipeline/Pipeline.hpp>
#include <vulkan/Device.hpp>
#include <engine/material/Shader.hpp>
#include <world/IChunk.hpp>

#include <algorithm>
#include <iterator>
#include <vulkan/vulkan.h>
#include <string.h>

using namespace CubA4::render::vulkan;
using namespace CubA4::render::engine::material;

PipelineBuilderBase::PipelineBuilderBase(std::shared_ptr<const Device> device, CubA4::render::config::VulkanConfigAdapter config) :
	device_(device), config_(config)
{
    fillDefaults();
}

PipelineBuilderBase::~PipelineBuilderBase()
{

}

void PipelineBuilderBase::useShader(std::shared_ptr<const IShader> shader)
{
	auto removePred = [shader](const std::shared_ptr<const IShader> &oldShader)
	{
		return shader->getType() == oldShader->getType();
	};
	auto it = std::remove_if(shaders_.begin(), shaders_.end(), removePred);
	//shaders_.erase(it, shaders_.end());
	shaders_.push_back(shader);
}

void PipelineBuilderBase::addBuiltInDescriptorSetLayout(sVkDescriptorSetLayout builtInLayout)
{
	descriptorSetLayouts_.push_back(builtInLayout);
}

void PipelineBuilderBase::addBuiltInDescriptorSetLayouts(const std::vector<sVkDescriptorSetLayout> &builtInLayouts)
{
	std::copy(builtInLayouts.begin(), builtInLayouts.end(), std::back_inserter(descriptorSetLayouts_));
}

VkGraphicsPipelineCreateInfo PipelineBuilderBase::build()
{
	prepareDescriptorSets();
	preparePushConstants();

	//Create pipeline layout
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

	std::vector<VkDescriptorSetLayout> layouts;
	auto transformFunction = [](sVkDescriptorSetLayout pLayout) -> VkDescriptorSetLayout
	{
		return pLayout->get();
	};
	std::transform(descriptorSetLayouts_.begin(), descriptorSetLayouts_.end(), std::back_inserter(layouts), transformFunction);

	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(layouts.size());
	pipelineLayoutInfo.pSetLayouts = layouts.data();

	pipelineLayoutInfo.pushConstantRangeCount = static_cast<uint32_t>(pushConstantsRanges_.size());
	pipelineLayoutInfo.pPushConstantRanges = pushConstantsRanges_.data();
	if (vkCreatePipelineLayout(device_->getDevice(), &pipelineLayoutInfo, nullptr, &pipelineLayout_) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
	}

	//Create pipeline
	prepareStages();
	prepareVertexInput();
	prepareInputAssembly();
	prepareRasterization();
	prepareMultisampling();
	prepareDepthStencil();
	prepareColorBlending();
	prepareDynmaic();
	prepareViewport();

	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.pVertexInputState = &vertexInputInfo_;
	pipelineInfo.pInputAssemblyState = &inputAssemblyInfo_;
	pipelineInfo.pRasterizationState = &rasterizationInfo_;
	pipelineInfo.pMultisampleState = &multisampleInfo_;
	pipelineInfo.pDepthStencilState = &depthStencilInfo_;
	pipelineInfo.pColorBlendState = &colorBlendInfo_;
	pipelineInfo.pViewportState = &viewportStateInfo_;
	pipelineInfo.pDynamicState = &dynamicStateInfo_;

	pipelineInfo.stageCount = static_cast<uint32_t>(stages_.size());
	pipelineInfo.pStages = stages_.data();

	pipelineInfo.layout = pipelineLayout_;

	return pipelineInfo;
}

void PipelineBuilderBase::fillPipelineInfo(PipelineInfo &pipelineInfo) const
{
	pipelineInfo.bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	pipelineInfo.layout = pipelineLayout_;
	pipelineInfo.shaders = shaders_;
	pipelineInfo.descriptorSetLayouts = descriptorSetLayouts_;
}

void PipelineBuilderBase::prepareStages()
{
	// TODO: Maybe make it protected?
	VkSpecializationMapEntry chunkSizeEntry = {};
	chunkSizeEntry.constantID = 0;
	chunkSizeEntry.offset = 0;
	chunkSizeEntry.size = sizeof(int32_t);
	vertexShaderSpecEntries_.push_back(chunkSizeEntry);

	vertexShaderSpecData_.resize(chunkSizeEntry.size);
	int32_t chunkSizeConst = CubA4::world::ChunkSize;
	memcpy(vertexShaderSpecData_.data(), &chunkSizeConst, chunkSizeEntry.size);

	vertexShaderSpec_.mapEntryCount = static_cast<uint32_t>(vertexShaderSpecEntries_.size());
	vertexShaderSpec_.pMapEntries = vertexShaderSpecEntries_.data();
	vertexShaderSpec_.dataSize = static_cast<uint32_t>(vertexShaderSpecData_.size());
	vertexShaderSpec_.pData = vertexShaderSpecData_.data();

	stages_.clear();
	std::for_each(shaders_.begin(), shaders_.end(), [this](std::shared_ptr<const IShader> shader)
	{
		VkPipelineShaderStageCreateInfo stageInfo = {};
		stageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		switch (shader->getType())
		{
		case ShaderType::Vertex:
			stageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
			stageInfo.pSpecializationInfo = &vertexShaderSpec_;
			break;
		case ShaderType::Fragment:
			stageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
			break;
		default:
			return;
		}
		auto vkShader = std::dynamic_pointer_cast<const Shader>(shader);
		stageInfo.module = vkShader->getShaderModule();
		stageInfo.pName = shader->getEntryPoint().data();
		stages_.push_back(stageInfo);
	});
}

void PipelineBuilderBase::prepareInputAssembly()
{
	inputAssemblyInfo_.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
}

void PipelineBuilderBase::prepareRasterization()
{
	rasterizationInfo_.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizationInfo_.cullMode = VK_CULL_MODE_NONE;
	rasterizationInfo_.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterizationInfo_.lineWidth = 1.f;
}

void PipelineBuilderBase::prepareDepthStencil()
{
	depthStencilInfo_.depthTestEnable = VK_TRUE;
	depthStencilInfo_.depthWriteEnable = VK_TRUE;
	depthStencilInfo_.depthCompareOp = VK_COMPARE_OP_LESS;
}

void PipelineBuilderBase::fillDefaults()
{
    vertexInputInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    inputAssemblyInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    rasterizationInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    multisampleInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    depthStencilInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    colorBlendInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    dynamicStateInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    viewportStateInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
}