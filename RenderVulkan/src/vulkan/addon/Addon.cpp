#include "./Addon.hpp" 
#include <algorithm>
using namespace CubA4::render::vulkan::addon;

Addon::Addon()
{
	
}

Addon::~Addon()
{
	
}

bool CubA4::render::vulkan::addon::Addon::available() const
{
	auto all = allNames();
	auto required = names();
	//Всё это необходимо отсортировать, прежде чем искать
	std::sort(all.begin(), all.end());
	std::sort(required.begin(), required.end());
	return std::includes(all.begin(), all.end(), required.begin(), required.end());
}
