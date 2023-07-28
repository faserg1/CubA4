#include <vulkan/pipeline/PipelineBuilderWireframe.hpp>
#include <vulkan/pipeline/Pipeline.hpp>
#include <vulkan/Device.hpp>
#include <engine/material/Shader.hpp>
#include <world/IChunk.hpp>

#include <algorithm>
#include <vulkan/vulkan.h>
#include <string.h>

using namespace CubA4::render::vulkan;
using namespace CubA4::render::engine::material;

PipelineBuilderWireframe::PipelineBuilderWireframe(std::shared_ptr<const Device> device, CubA4::render::config::VulkanConfigAdapter config) :
	PipelineBuilderBase(device, config)
{
}

PipelineBuilderWireframe::~PipelineBuilderWireframe()
{

}

void PipelineBuilderWireframe::prepareVertexInput()
{
	const uint16_t posSize = sizeof(float) * 3;
	const uint16_t colorSize = sizeof(float) * 3;
	const uint16_t vertexSize = posSize + colorSize;

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

void PipelineBuilderWireframe::prepareInputAssembly()
{
	inputAssemblyInfo_.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
}

void PipelineBuilderWireframe::prepareRasterization()
{
	rasterizationInfo_.polygonMode = VK_POLYGON_MODE_LINE;
	rasterizationInfo_.cullMode = VK_CULL_MODE_NONE;
	rasterizationInfo_.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterizationInfo_.lineWidth = 1.f;
}

void PipelineBuilderWireframe::prepareMultisampling()
{
	multisampleInfo_.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
}

void PipelineBuilderWireframe::prepareDepthStencil()
{
	depthStencilInfo_.depthTestEnable = VK_TRUE;
	depthStencilInfo_.depthWriteEnable = VK_TRUE;
	depthStencilInfo_.depthCompareOp = VK_COMPARE_OP_LESS;
}

void PipelineBuilderWireframe::prepareColorBlending()
{
	VkPipelineColorBlendAttachmentState clr = {};
	clr.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;

	colorAttachments_.push_back(clr);

	colorBlendInfo_.attachmentCount = static_cast<uint32_t>(colorAttachments_.size());
	colorBlendInfo_.pAttachments = colorAttachments_.data();
}

void PipelineBuilderWireframe::prepareDynmaic()
{
	dynamicStates_.push_back(VK_DYNAMIC_STATE_VIEWPORT);
	dynamicStates_.push_back(VK_DYNAMIC_STATE_SCISSOR);

	dynamicStateInfo_.dynamicStateCount = static_cast<uint32_t>(dynamicStates_.size());
	dynamicStateInfo_.pDynamicStates = dynamicStates_.data();
}

void PipelineBuilderWireframe::prepareViewport()
{
	viewportStateInfo_.viewportCount = 1;
	viewportStateInfo_.scissorCount = 1;
}

void PipelineBuilderWireframe::prepareDescriptorSets()
{
}

void PipelineBuilderWireframe::preparePushConstants()
{
	constexpr const auto chunkPositionSize = sizeof(CubA4::world::ChunkPos);

	VkPushConstantRange totalStageAllRange = {};
	totalStageAllRange.offset = 0;
	totalStageAllRange.size = chunkPositionSize;
	totalStageAllRange.stageFlags = VK_SHADER_STAGE_ALL;

	pushConstantsRanges_.push_back(totalStageAllRange);
}
