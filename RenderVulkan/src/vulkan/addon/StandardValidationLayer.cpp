#include "./StandardValidationLayer.hpp" 
#include <vulkan/vulkan.h>
using namespace CubA4::render::vulkan::addon;
using namespace CubA4::render::vulkan;

StandardValidationLayer::StandardValidationLayer()
{
	
}

StandardValidationLayer::~StandardValidationLayer()
{
	
}

std::vector<std::string> StandardValidationLayer::names() const
{
	return {"VK_LAYER_LUNARG_standard_validation"};
}

void StandardValidationLayer::init(std::shared_ptr<const Instance> instance)
{
}

void StandardValidationLayer::destroy(std::shared_ptr<const Instance> instance)
{
}

void StandardValidationLayer::added(InstanceBuilder &builder)
{

}
