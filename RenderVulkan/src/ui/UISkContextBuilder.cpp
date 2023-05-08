#include <ui/UISkContextBuilder.hpp>
#include <skia/include/gpu/vk/GrVkBackendContext.h>
#include <skia/include/gpu/GrDirectContext.h>
using namespace CubA4::ui;
using namespace CubA4::render::vulkan;


UISkContextBuilder::UISkContextBuilder(std::shared_ptr<Instance> instance,
            std::shared_ptr<PhysicalDevice> physDevice,
            std::shared_ptr<Device> device) :
	instance_(instance), physDevice_(physDevice), device_(device)
{

}

std::shared_ptr<UISkContext> UISkContextBuilder::createContext()
{
	// https://skia.org/docs/user/special/vulkan/
	GrVkBackendContext backendContext;
	backendContext.fInstance = instance_->getInstance();
	backendContext.fPhysicalDevice = physDevice_->getPhysicalDevice();
	backendContext.fDevice = device_->getDevice();
	backendContext.fQueue = device_->getQueue()->get();
	auto context = GrDirectContext::MakeVulkan(backendContext);
	return std::make_shared<UISkContext>(context);
}
