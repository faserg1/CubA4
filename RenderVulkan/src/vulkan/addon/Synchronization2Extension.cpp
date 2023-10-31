#include <vulkan./addon/Synchronization2Extension.hpp>
#include <vulkan/vulkan.h>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::vulkan::addon;

Synchronization2Extension::Synchronization2Extension(std::weak_ptr<PhysicalDevice> physicalDevice) :
	DeviceExtension(physicalDevice)
{
	
}

Synchronization2Extension::~Synchronization2Extension()
{
	
}

std::vector<std::string> Synchronization2Extension::names() const
{
	return { VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME };
}

void Synchronization2Extension::init(std::shared_ptr<const Device> instance)
{

}

void Synchronization2Extension::destroy(std::shared_ptr<const Device> instance)
{

}

void Synchronization2Extension::added(DeviceBuilder &builder)
{

}