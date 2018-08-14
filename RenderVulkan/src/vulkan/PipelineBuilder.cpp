#include "./PipelineBuilder.hpp"
using namespace CubA4::render::vulkan;

PipelineBuilder::PipelineBuilder(std::shared_ptr<const Device> device) :
	device_(device)
{
	vertexInputInfo_ = {};
	inputAssemblyInfo_ = {};
	rasterizationInfo_ = {};
	multisampleInfo_ = {};
	depthStencilInfo_ = {};
	colorBlendInfo_ = {};
	dynamicInfo_ = {};
}

PipelineBuilder::~PipelineBuilder()
{
	
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

}

void PipelineBuilder::prepareRasterization()
{

}

void PipelineBuilder::prepareMultisampling()
{

}

void PipelineBuilder::prepareDepthStencil()
{

}

void PipelineBuilder::prepareColorBlending()
{

}

void PipelineBuilder::prepareDynamics()
{

}

void PipelineBuilder::prepareDescriptorSets()
{

}
