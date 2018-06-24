#include "./VulkanInstanceAddon.hpp"
using namespace CubA4::render::vulkan::addon;

VulkanInstanceAddon::VulkanInstanceAddon()
{

}

VulkanInstanceAddon::~VulkanInstanceAddon()
{

}

VulkanAddonType VulkanInstanceAddon::type() const
{
	return VulkanAddonType::Instance;
}