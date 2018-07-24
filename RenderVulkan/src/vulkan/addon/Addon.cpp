#include "./Addon.hpp"
#include <algorithm>
using namespace CubA4::render::vulkan::addon;

Addon::Addon()
{
	
}

Addon::~Addon()
{
	
}

bool Addon::available() const
{
	auto all = allNames();
	auto required = names();
	//Всё это необходимо отсортировать, прежде чем искать
	std::sort(all.begin(), all.end());
	std::sort(required.begin(), required.end());
	return std::includes(all.begin(), all.end(), required.begin(), required.end());
}

std::string Addon::joinNames() const
{
	std::string temp;
	auto names = this->names();
	std::for_each(names.begin(), names.end(), [&](std::string &name)
	{
		temp += name + ",";
	});
	temp.pop_back();
	return temp;
}