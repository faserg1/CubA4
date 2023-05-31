#include "./Instance.hpp"
using namespace CubA4::render::vulkan;

Instance::Instance(VkInstance instance, uint32_t apiVersion) :
	instance_(instance), apiVersion_(apiVersion)
{
	
}

Instance::~Instance()
{
	
}

VkInstance Instance::getInstance() const
{
	return instance_;
}

uint32_t Instance::getAPIVersion() const
{
	return apiVersion_;
}