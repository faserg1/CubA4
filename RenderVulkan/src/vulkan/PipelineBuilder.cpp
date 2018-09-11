#include "./PipelineBuilder.hpp"
#include "./Pipeline.hpp"
#include "./Device.hpp"
#include "../engine/material/Shader.hpp"

#include <algorithm>

using namespace CubA4::render::vulkan;
using namespace CubA4::render::engine::material;

PipelineBuilder::PipelineBuilder(std::shared_ptr<const Device> device) :
	device_(device)
{
	vertexInputInfo_ = {};
	inputAssemblyInfo_ = {};
	rasterizationInfo_ = {};
	multisampleInfo_ = {};
	depthStencilInfo_ = {};
	colorBlendInfo_ = {};
	dynamicStateInfo_ = {};
	viewportStateInfo_ = {};
}

PipelineBuilder::~PipelineBuilder()
{
	
}

void PipelineBuilder::useShader(std::shared_ptr<const IShader> shader)
{
	auto removePred = [shader](const std::shared_ptr<const IShader> &oldShader)
	{
		return shader->getType() == oldShader->getType();
	};
	std::remove_if(shaders_.begin(), shaders_.end(), removePred);
	shaders_.push_back(shader);
}

VkGraphicsPipelineCreateInfo PipelineBuilder::build()
{
	prepareDescriptorSets();
	preparePushConstants();

	//Create pipeline layout
	VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts_.size());
	pipelineLayoutInfo.pSetLayouts = descriptorSetLayouts_.data();
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

void PipelineBuilder::fillPipelineInfo(PipelineInfo &pipelineInfo) const
{
	pipelineInfo.bindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	pipelineInfo.layout = pipelineLayout_;
	pipelineInfo.shaders = shaders_;
	pipelineInfo.descriptorSetLayouts = descriptorSetLayouts_;
}

void PipelineBuilder::prepareStages()
{
	stages_.clear();
	std::for_each(shaders_.begin(), shaders_.end(), [this](std::shared_ptr<const IShader> shader)
	{
		VkPipelineShaderStageCreateInfo stageInfo = {};
		stageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		switch (shader->getType())
		{
		case ShaderType::Vertex:
			stageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
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

void PipelineBuilder::prepareVertexInput()
{
	vertexInputInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	const uint16_t posSize = sizeof(float) * 3;
	const uint16_t vertexSize = posSize;

	vertexBindingDescriptions_.push_back(
		{
			0, //binding
			vertexSize, //stride
			VK_VERTEX_INPUT_RATE_VERTEX
		}
	);

	vertexAttrDescriptions_.push_back(
		{
			0, //location
			0, //binding
			VK_FORMAT_R32G32B32_SFLOAT, //format,
			0
		}
	);

	vertexInputInfo_.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexBindingDescriptions_.size());
	vertexInputInfo_.pVertexBindingDescriptions = vertexBindingDescriptions_.data();
	vertexInputInfo_.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexAttrDescriptions_.size());
	vertexInputInfo_.pVertexAttributeDescriptions = vertexAttrDescriptions_.data();
	
}

void PipelineBuilder::prepareInputAssembly()
{
	inputAssemblyInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssemblyInfo_.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
}

void PipelineBuilder::prepareRasterization()
{
	rasterizationInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizationInfo_.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizationInfo_.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizationInfo_.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterizationInfo_.lineWidth = 1.f;
}

void PipelineBuilder::prepareMultisampling()
{
	multisampleInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampleInfo_.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
}

void PipelineBuilder::prepareDepthStencil()
{
	depthStencilInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	depthStencilInfo_.depthTestEnable = VK_TRUE;
	depthStencilInfo_.depthWriteEnable = VK_TRUE;
	depthStencilInfo_.depthCompareOp = VK_COMPARE_OP_LESS;
}

void PipelineBuilder::prepareColorBlending()
{
	colorBlendInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;

	VkPipelineColorBlendAttachmentState clr = {};
	clr.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

	colorAttachments_.push_back(clr);

	colorBlendInfo_.attachmentCount = static_cast<uint32_t>(colorAttachments_.size());
	colorBlendInfo_.pAttachments = colorAttachments_.data();
}

void PipelineBuilder::prepareDynmaic()
{
	dynamicStateInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;

	dynamicStates_.push_back(VK_DYNAMIC_STATE_VIEWPORT);
	dynamicStates_.push_back(VK_DYNAMIC_STATE_SCISSOR);

	dynamicStateInfo_.dynamicStateCount = static_cast<uint32_t>(dynamicStates_.size());
	dynamicStateInfo_.pDynamicStates = dynamicStates_.data();
}

void PipelineBuilder::prepareViewport()
{
	viewportStateInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;

	viewports_.push_back({});
	scissors_.push_back({});

	viewportStateInfo_.viewportCount = static_cast<uint32_t>(viewports_.size());
	viewportStateInfo_.scissorCount = static_cast<uint32_t>(scissors_.size());
	viewportStateInfo_.pViewports = viewports_.data();
	viewportStateInfo_.pScissors = scissors_.data();
}

void PipelineBuilder::prepareDescriptorSets()
{
	VkDescriptorSetLayoutBinding bindingInfos[2] = {};
	//Instance info
	bindingInfos[0].binding = 0;
	bindingInfos[0].descriptorCount = 1;
	bindingInfos[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	bindingInfos[0].stageFlags = VK_SHADER_STAGE_ALL;
	//Matrix info
	bindingInfos[1].binding = 1;
	bindingInfos[1].descriptorCount = 1;
	bindingInfos[1].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	bindingInfos[1].stageFlags = VK_SHADER_STAGE_ALL;
	VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo = {};
	descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptorSetLayoutInfo.bindingCount = 2;
	descriptorSetLayoutInfo.pBindings = bindingInfos;
	VkDescriptorSetLayout descriptorSetLayout;
	if (vkCreateDescriptorSetLayout(device_->getDevice(), &descriptorSetLayoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
	}
	descriptorSetLayouts_.push_back(descriptorSetLayout);
}

void PipelineBuilder::preparePushConstants()
{
	
}