#include "./VulkanInstanceAddon.hpp"
#include <algorithm>
using namespace CubA4::render::vulkan::addon;

bool CubA4::render::vulkan::addon::VulkanInstanceAddon::available() const
{
	auto all = allNames();
	auto required = names();
	return std::includes(all.begin(), all.end(), required.begin(), required.end());
}
