#include <ui/UISkContextBuilder.hpp>
#include <skia/include/gpu/vk/GrVkBackendContext.h>
#include <skia/include/gpu/GrDirectContext.h>
using namespace CubA4::render::ui;
using namespace CubA4::render::vulkan;


UISkContextBuilder::UISkContextBuilder(std::shared_ptr<const Instance> instance,
            std::shared_ptr<const Device> device) :
	instance_(instance), device_(device)
{

}

std::shared_ptr<UISkContext> UISkContextBuilder::createContext()
{
	// https://skia.org/docs/user/special/vulkan/
	GrVkBackendContext backendContext;
	backendContext.fInstance = instance_->getInstance();
	backendContext.fPhysicalDevice = device_->getPhysicalDevice();
	backendContext.fDevice = device_->getDevice();
	backendContext.fQueue = device_->getQueue()->get();
	auto context = GrDirectContext::MakeVulkan(backendContext);
	return std::make_shared<UISkContext>(context);
}
