#include <ui/UISkContextBuilder.hpp>
#include <skia/include/gpu/vk/GrVkBackendContext.h>
#include <skia/include/gpu/vk/GrVkExtensions.h>
#include <skia/include/gpu/GrDirectContext.h>
#include <algorithm>
using namespace CubA4::render::ui;
using namespace CubA4::render::vulkan;


UISkContextBuilder::UISkContextBuilder(std::shared_ptr<const Instance> instance,
            std::shared_ptr<const Device> device) :
	instance_(instance), device_(device)
{

}

std::shared_ptr<UISkContext> UISkContextBuilder::createContext()
{
	GrVkGetProc proc = std::function([](const char *funcName,
        VkInstance instance,
        VkDevice device) -> PFN_vkVoidFunction
	{
		if (device)
		{
			if (auto func = vkGetDeviceProcAddr(device, funcName))
				return func;
		}
		if (auto func = vkGetInstanceProcAddr(instance, funcName))
			return func;
		return nullptr;
	});

	GrVkExtensions extensions;
	std::vector<const char *> enabledExtensions(device_->getEnabledExtensions().size());
	std::transform(device_->getEnabledExtensions().begin(), device_->getEnabledExtensions().end(), enabledExtensions.begin(), [](const std::string &name) -> const char *
	{
		return name.data();
	});

	extensions.init(proc, instance_->getInstance(), device_->getPhysicalDevice(), 0, nullptr, static_cast<uint32_t>(enabledExtensions.size()), enabledExtensions.data());

	// https://skia.org/docs/user/special/vulkan/
	GrVkBackendContext backendContext {};
	backendContext.fInstance = instance_->getInstance();
	backendContext.fPhysicalDevice = device_->getPhysicalDevice();
	backendContext.fDevice = device_->getDevice();
	backendContext.fQueue = device_->getQueue()->get();
	backendContext.fMaxAPIVersion = instance_->getAPIVersion();
	backendContext.fGetProc = proc;
	backendContext.fVkExtensions = &extensions;
	backendContext.fDeviceFeatures2 = &device_->getEnabledFeatures();
	auto context = GrDirectContext::MakeVulkan(backendContext);
	return std::make_shared<UISkContext>(context);
}
