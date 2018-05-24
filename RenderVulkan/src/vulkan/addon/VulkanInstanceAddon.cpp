#include "./VulkanInstanceAddon.hpp"
#include <algorithm>
using namespace CubA4::render::vulkan::addon;

bool CubA4::render::vulkan::addon::VulkanInstanceAddon::available() const
{
	auto all = allNames();
	auto required = names();
	//Всё это необходимо отсортировать, прежде чем искать
	std::sort(all.begin(), all.end());
	std::sort(required.begin(), required.end());
	return std::includes(all.begin(), all.end(), required.begin(), required.end());
}
