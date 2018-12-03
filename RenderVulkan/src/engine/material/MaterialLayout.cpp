#include "./MaterialLayout.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialLayout::MaterialLayout(std::shared_ptr<Pipeline> pipeline) :
	pipeline_(pipeline)
{
	
}

MaterialLayout::~MaterialLayout()
{
	
}

std::shared_ptr<Pipeline> MaterialLayout::getPipeline() const
{
	return pipeline_;
}