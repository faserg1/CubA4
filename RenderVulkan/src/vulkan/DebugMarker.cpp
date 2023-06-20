#include "./DebugMarker.hpp"
#include "./Device.hpp"
using namespace CubA4::render::vulkan;

#define getVkFuncDevicePtr(device, funcName) (PFN_##funcName)(vkGetDeviceProcAddr(device.getDevice(), #funcName))

DebugMarker::DebugMarker(const Device &device) :
	device_(device), setName_(nullptr), setTag_(nullptr)
{
	setName_ = getVkFuncDevicePtr(device, vkSetDebugUtilsObjectNameEXT);
	setTag_ = getVkFuncDevicePtr(device, vkSetDebugUtilsObjectTagEXT);
	cmdBegin_ = getVkFuncDevicePtr(device, vkCmdBeginDebugUtilsLabelEXT);
	cmdEnd_ = getVkFuncDevicePtr(device, vkCmdEndDebugUtilsLabelEXT);
	cmdInsert_ = getVkFuncDevicePtr(device, vkCmdInsertDebugUtilsLabelEXT);
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
	if (!setName_)
		return;
	VkDebugUtilsObjectNameInfoEXT nameInfo = {};
	nameInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT;
	nameInfo.objectType = objectType;
	nameInfo.objectHandle = object;
	nameInfo.pObjectName = name;
	setName_(device_.getDevice(), &nameInfo);
}

void DebugMarker::setTag(uint64_t object, VkObjectType objectType)
{
	if (!setTag_)
		return;
	VkDebugUtilsObjectTagInfoEXT tagInfo = {};
	tagInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_TAG_INFO_EXT;
	tagInfo.objectType = objectType;
	tagInfo.objectHandle = object;
	// TODO:
}

void DebugMarker::cmdLabelBegin(VkCommandBuffer cmd, const std::string &name, std::array<float, 4> color)
{
	if (!cmdBegin_)
		return;
	VkDebugUtilsLabelEXT info {
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
		.pLabelName = name.c_str(),
		.color = {color[0], color[1], color[2], color[3]}
	};
	cmdBegin_(cmd, &info);
}

void DebugMarker::cmdLabelEnd(VkCommandBuffer cmd)
{
	if (!cmdEnd_)
		return;
	cmdEnd_(cmd);
}

void DebugMarker::cmdLabelInsert(VkCommandBuffer cmd, const std::string &name, std::array<float, 4> color)
{
	if (!cmdInsert_)
		return;
	VkDebugUtilsLabelEXT info {
		.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
		.pLabelName = name.c_str(),
		.color = {color[0], color[1], color[2], color[3]}
	};
	cmdInsert_(cmd, &info);
}