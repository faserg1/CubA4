#include "./InstanceAddon.hpp"
using namespace CubA4::render::vulkan::addon;

InstanceAddon::InstanceAddon()
{

}

InstanceAddon::~InstanceAddon()
{

}

AddonType InstanceAddon::type() const
{
	return AddonType::Instance;
}