#include <vulkan/pipeline/PipelineBuilderMaterial.hpp>
#include <vulkan/pipeline/Pipeline.hpp>
#include <vulkan/Device.hpp>
#include <engine/material/Shader.hpp>
#include <world/IChunk.hpp>

#include <algorithm>
#include <vulkan/vulkan.h>
#include <string.h>

using namespace CubA4::render::vulkan;
using namespace CubA4::render::engine::material;

PipelineBuilderMaterial::PipelineBuilderMaterial(std::shared_ptr<const Device> device, CubA4::render::config::VulkanConfigAdapter config) :
	PipelineBuilderBase(device, config)
{
}

PipelineBuilderMaterial::~PipelineBuilderMaterial()
{

}

void PipelineBuilderMaterial::addTexture()
{
	textureCount++;
}

sVkDescriptorSetLayout PipelineBuilderMaterial::getTextureLayout()
{
	return textureLayout_;
}

void PipelineBuilderMaterial::prepareVertexInput()
{
	const uint16_t posSize = sizeof(float) * 3;
	const uint16_t uvwSize = sizeof(float) * 3;
	const uint16_t vertexSize = posSize + uvwSize;

	// Bindings

	vertexBindingDescriptions_.push_back(
		{
			0, //binding
			vertexSize, //stride
			VK_VERTEX_INPUT_RATE_VERTEX //input rate
		}
	);

	//Attributes

	vertexAttrDescriptions_.push_back(
		{
			0, //location
			0, //binding
			VK_FORMAT_R32G32B32_SFLOAT, //format,
			0, //offset
		}
	);

	vertexAttrDescriptions_.push_back(
		{
			1, //location
			0, //binding
			VK_FORMAT_R32G32B32_SFLOAT, //format,
			posSize, //offset
		}
	);

	vertexInputInfo_.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexBindingDescriptions_.size());
	vertexInputInfo_.pVertexBindingDescriptions = vertexBindingDescriptions_.data();
	vertexInputInfo_.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexAttrDescriptions_.size());
	vertexInputInfo_.pVertexAttributeDescriptions = vertexAttrDescriptions_.data();

}

void PipelineBuilderMaterial::prepareInputAssembly()
{
	inputAssemblyInfo_.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
}

void PipelineBuilderMaterial::prepareRasterization()
{
	rasterizationInfo_.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizationInfo_.cullMode = VK_CULL_MODE_NONE;
	rasterizationInfo_.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterizationInfo_.lineWidth = 1.f;
}

void PipelineBuilderMaterial::prepareMultisampling()
{
	multisampleInfo_.rasterizationSamples = config_.getAntialiasing();
}

void PipelineBuilderMaterial::prepareDepthStencil()
{
	depthStencilInfo_.depthTestEnable = VK_TRUE;
	depthStencilInfo_.depthWriteEnable = VK_TRUE;
	depthStencilInfo_.depthCompareOp = VK_COMPARE_OP_LESS;
}

void PipelineBuilderMaterial::prepareColorBlending()
{
	VkPipelineColorBlendAttachmentState clr = {};
	clr.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

	colorAttachments_.push_back(clr);

	colorBlendInfo_.attachmentCount = static_cast<uint32_t>(colorAttachments_.size());
	colorBlendInfo_.pAttachments = colorAttachments_.data();
}

void PipelineBuilderMaterial::prepareDynmaic()
{
	dynamicStates_.push_back(VK_DYNAMIC_STATE_VIEWPORT);
	dynamicStates_.push_back(VK_DYNAMIC_STATE_SCISSOR);

	dynamicStateInfo_.dynamicStateCount = static_cast<uint32_t>(dynamicStates_.size());
	dynamicStateInfo_.pDynamicStates = dynamicStates_.data();
}

void PipelineBuilderMaterial::prepareViewport()
{
	viewportStateInfo_.viewportCount = 1;
	viewportStateInfo_.scissorCount = 1;
}

void PipelineBuilderMaterial::prepareDescriptorSets()
{
	if (!textureCount)
		return;
	VkDescriptorSetLayoutBinding textureInfo = {};
	//Texture info
	textureInfo.binding = 2;
	textureInfo.descriptorCount = textureCount;
	textureInfo.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	textureInfo.stageFlags = VK_SHADER_STAGE_ALL;

	VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo = {};
	descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptorSetLayoutInfo.bindingCount = 1;
	descriptorSetLayoutInfo.pBindings = &textureInfo;
	VkDescriptorSetLayout layout = {};
	if (vkCreateDescriptorSetLayout(device_->getDevice(), &descriptorSetLayoutInfo, nullptr, &layout) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exceptions, etc
		return;
	}
	device_->getMarker().setName(layout, "texture layout");

	std::function<void(VkDescriptorSetLayout)> deleter = [dev = device_](VkDescriptorSetLayout layout)
	{
		vkDestroyDescriptorSetLayout(dev->getDevice(), layout, nullptr);
	};
	textureLayout_ = util::createSharedVulkanObject(layout, deleter);
	descriptorSetLayouts_.push_back(textureLayout_);
}

void PipelineBuilderMaterial::preparePushConstants()
{
	constexpr const auto chunkPositionSize = sizeof(CubA4::world::ChunkPos);

	VkPushConstantRange totalStageAllRange = {};
	totalStageAllRange.offset = 0;
	totalStageAllRange.size = chunkPositionSize;
	totalStageAllRange.stageFlags = VK_SHADER_STAGE_ALL;

	pushConstantsRanges_.push_back(totalStageAllRange);
}
