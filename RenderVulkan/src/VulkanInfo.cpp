#include "VulkanInfo.hpp"

using namespace CubA4::render;

VulkanInfo::VulkanInfo()
{

}

VulkanInfo::~VulkanInfo()
{

}

std::string CubA4::render::VulkanInfo::getRenderEngineName() const
{
	return "Vulkan";
}

RenderEngine * CubA4::render::VulkanInfo::getRenderEngine()
{
	return nullptr;
}
