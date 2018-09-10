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
	prepareVertexInput();
	prepareInputAssembly();
	prepareRasterization();
	prepareMultisampling();
	prepareDepthStencil();
	prepareColorBlending();

	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.pVertexInputState = &vertexInputInfo_;
	pipelineInfo.pInputAssemblyState = &inputAssemblyInfo_;
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

void PipelineBuilder::prepareDescriptorSets()
{
	//Instance info
	VkDescriptorSetLayoutBinding bindingInfo = {};
	bindingInfo.binding = 0;
	bindingInfo.descriptorCount = 1;
	bindingInfo.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	bindingInfo.stageFlags = VK_SHADER_STAGE_ALL;
	VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo = {};
	descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptorSetLayoutInfo.bindingCount = 1;
	descriptorSetLayoutInfo.pBindings = &bindingInfo;
	VkDescriptorSetLayout descriptorSetLayout;
	if (vkCreateDescriptorSetLayout(device_->getDevice(), &descriptorSetLayoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
	}
	descriptorSetLayouts_.push_back(descriptorSetLayout);
}

void PipelineBuilder::preparePushConstants()
{
	uint16_t floatMatrixSize = sizeof(float) * 16;
	VkPushConstantRange worldMatrixRange, viewMatrixRange, projectionMatrixRange;
	worldMatrixRange.offset = 0;
	worldMatrixRange.size = floatMatrixSize;
	worldMatrixRange.stageFlags = VK_SHADER_STAGE_ALL;

	worldMatrixRange.offset = floatMatrixSize;
	worldMatrixRange.size = floatMatrixSize;
	worldMatrixRange.stageFlags = VK_SHADER_STAGE_ALL;

	worldMatrixRange.offset = floatMatrixSize * 2;
	worldMatrixRange.size = floatMatrixSize;
	worldMatrixRange.stageFlags = VK_SHADER_STAGE_ALL;

	pushConstantsRanges_.push_back(worldMatrixRange);
	pushConstantsRanges_.push_back(viewMatrixRange);
	pushConstantsRanges_.push_back(projectionMatrixRange);
}