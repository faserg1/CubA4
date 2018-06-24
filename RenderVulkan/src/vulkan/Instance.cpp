#include "./Instance.hpp"
using namespace CubA4::render::vulkan;

Instance::Instance(VkInstance instance) :
	instance_(instance)
{
	
}

Instance::~Instance()
{
	
}

VkInstance Instance::getInstance() const
{
	return instance_;
}