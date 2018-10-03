#include "./DebugMarker.hpp"
#include "./Device.hpp"
using namespace CubA4::render::vulkan;

DebugMarker::DebugMarker(const Device &device) :
	device_(device)
{
	setName_ = (PFN_vkSetDebugUtilsObjectNameEXT) vkGetDeviceProcAddr(device.getDevice(), "vkSetDebugUtilsObjectNameEXT");
	setTag_ = (PFN_vkSetDebugUtilsObjectTagEXT) vkGetDeviceProcAddr(device.getDevice(), "vkSetDebugUtilsObjectTagEXT");
}

DebugMarker::~DebugMarker()
{
	
}

VkObjectType DebugMarker::getObjectType(const std::type_info &typeInfo)
{
	if (typeid(VkInstance) == typeInfo)
		return VK_OBJECT_TYPE_INSTANCE;
	if (typeid(VkPhysicalDevice) == typeInfo)
		return VK_OBJECT_TYPE_UNKNOWN; // VK_OBJECT_TYPE_PHYSICAL_DEVICE; // Bug with naming VkPhysicalDevice
	if (typeid(VkDevice) == typeInfo)
		return VK_OBJECT_TYPE_DEVICE;
	if (typeid(VkQueue) == typeInfo)
		return VK_OBJECT_TYPE_UNKNOWN; // VK_OBJECT_TYPE_QUEUE; // Bug with naming VkQueue
	if (typeid(VkSemaphore) == typeInfo)
		return VK_OBJECT_TYPE_SEMAPHORE;
	if (typeid(VkCommandBuffer) == typeInfo)
		return VK_OBJECT_TYPE_COMMAND_BUFFER;
	if (typeid(VkFence) == typeInfo)
		return VK_OBJECT_TYPE_FENCE;
	if (typeid(VkDeviceMemory) == typeInfo)
		return VK_OBJECT_TYPE_DEVICE_MEMORY;
	if (typeid(VkBuffer) == typeInfo)
		return VK_OBJECT_TYPE_BUFFER;
	if (typeid(VkImage) == typeInfo)
		return VK_OBJECT_TYPE_IMAGE;
	if (typeid(VkEvent) == typeInfo)
		return VK_OBJECT_TYPE_EVENT;
	if (typeid(VkQueryPool) == typeInfo)
		return VK_OBJECT_TYPE_QUERY_POOL;
	if (typeid(VkBufferView) == typeInfo)
		return VK_OBJECT_TYPE_BUFFER_VIEW;
	if (typeid(VkImageView) == typeInfo)
		return VK_OBJECT_TYPE_IMAGE_VIEW;
	if (typeid(VkShaderModule) == typeInfo)
		return VK_OBJECT_TYPE_SHADER_MODULE;
	if (typeid(VkPipelineCache) == typeInfo)
		return VK_OBJECT_TYPE_PIPELINE_CACHE;
	if (typeid(VkPipelineLayout) == typeInfo)
		return VK_OBJECT_TYPE_PIPELINE_LAYOUT;
	if (typeid(VkRenderPass) == typeInfo)
		return VK_OBJECT_TYPE_RENDER_PASS;
	if (typeid(VkPipeline) == typeInfo)
		return VK_OBJECT_TYPE_PIPELINE;
	if (typeid(VkDescriptorSetLayout) == typeInfo)
		return VK_OBJECT_TYPE_DESCRIPTOR_SET_LAYOUT;
	if (typeid(VkSampler) == typeInfo)
		return VK_OBJECT_TYPE_SAMPLER;
	if (typeid(VkDescriptorPool) == typeInfo)
		return VK_OBJECT_TYPE_DESCRIPTOR_POOL;
	if (typeid(VkDescriptorSet) == typeInfo)
		return VK_OBJECT_TYPE_DESCRIPTOR_SET;
	if (typeid(VkFramebuffer) == typeInfo)
		return VK_OBJECT_TYPE_FRAMEBUFFER;
	if (typeid(VkCommandPool) == typeInfo)
		return VK_OBJECT_TYPE_COMMAND_POOL;

	if (typeid(VkSurfaceKHR) == typeInfo)
		return VK_OBJECT_TYPE_SURFACE_KHR;
	if (typeid(VkSwapchainKHR) == typeInfo)
		return VK_OBJECT_TYPE_SWAPCHAIN_KHR;
	return VK_OBJECT_TYPE_UNKNOWN;
}

void DebugMarker::setName(uint64_t object, VkObjectType objectType, const char *name)
{
	VkDebugUtilsObjectNameInfoEXT nameInfo = {};
	nameInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
	nameInfo.objectType = objectType;
	nameInfo.objectHandle = object;
	nameInfo.pObjectName = name;
	setName_(device_.getDevice(), &nameInfo);
}