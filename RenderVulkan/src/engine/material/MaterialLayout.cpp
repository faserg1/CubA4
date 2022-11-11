#include "./MaterialLayout.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialLayout::MaterialLayout(std::shared_ptr<Pipeline> pipeline, sVkDescriptorSetLayout textureLayout) :
	pipeline_(pipeline), textureLayout_(textureLayout)
{
	
}

MaterialLayout::~MaterialLayout()
{
	
}

std::shared_ptr<Pipeline> MaterialLayout::getPipeline() const
{
	return pipeline_;
}

sVkDescriptorSetLayout MaterialLayout::getLayout() const
{
	return textureLayout_;
}
