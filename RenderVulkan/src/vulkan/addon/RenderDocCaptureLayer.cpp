#include <vulkan/addon/RenderDocCaptureLayer.hpp>
#include <vulkan/vulkan.h>
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::render::vulkan;

RenderDocCaptureLayer::RenderDocCaptureLayer()
{
	
}

RenderDocCaptureLayer::~RenderDocCaptureLayer()
{
	
}

std::vector<std::string> RenderDocCaptureLayer::names() const
{
	std::vector<std::string> name = {
		"VK_LAYER_RENDERDOC_Capture"
	};
	if (checkNames(name))
		return std::move(name);
	return {};
}

void RenderDocCaptureLayer::init(std::shared_ptr<const Instance> instance)
{
}

void RenderDocCaptureLayer::destroy(std::shared_ptr<const Instance> instance)
{
}

void RenderDocCaptureLayer::added(InstanceBuilder &builder)
{

}


