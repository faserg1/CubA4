#include "./MemoryAllocator.hpp"
#include "../vulkan/Device.hpp"
#include "../vulkan/Memory.hpp"
#include <vector>
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

static int32_t findProperties(const VkPhysicalDeviceMemoryProperties* pMemoryProperties, uint32_t memoryTypeBitsRequirement, VkMemoryPropertyFlags requiredProperties);
static std::vector<uint32_t> findProperties2(const VkPhysicalDeviceMemoryProperties* pMemoryProperties, uint32_t memoryTypeBitsRequirement, VkMemoryPropertyFlags requiredProperties);

MemoryAllocator::MemoryAllocator(std::shared_ptr<const Device> device) :
	device_(device)
{
	
}

MemoryAllocator::~MemoryAllocator()
{
	
}

std::shared_ptr<Memory> MemoryAllocator::allocate(size_t size, MemoryAllocationPrefered preference, uint32_t supportedTypes)
{
	VkDeviceMemory memory = {};
	VkMemoryAllocateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	info.allocationSize = static_cast<VkDeviceSize>(size);
	//TODO: [OOKAMI] Choose index
	VkPhysicalDeviceMemoryProperties props;
	vkGetPhysicalDeviceMemoryProperties(device_->getPhysicalDevice(), &props);
	VkMemoryPropertyFlags requiredFlags = {};
	switch (preference)
	{
	case MemoryAllocationPrefered::Device:
		requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		break;
	case MemoryAllocationPrefered::Host:
		requiredFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
		break;
	default:
		//TODO: [OOKAMI] Throw exception
		return {};
	}
	/*int32_t index = findProperties(&props, supportedTypes, requiredFlags);
	if (index < 0)
		//TODO: [OOKAMI] Throw exception
		return {};*/
	auto availableIndices = findProperties2(&props, supportedTypes, requiredFlags);
	for (auto memIndex : availableIndices)
	{
		info.memoryTypeIndex = memIndex;
		auto result = vkAllocateMemory(device_->getDevice(), &info, nullptr, &memory);
		if (result == VK_SUCCESS)
			break;
	}
	if (!memory)
	{
		//TODO: [OOKAMI] Throw exception
		return {};
	}
	return std::make_shared<Memory>(device_, memory, info.allocationSize, props.memoryTypes[info.memoryTypeIndex].propertyFlags, info.memoryTypeIndex);
}

std::shared_ptr<Memory> MemoryAllocator::allocateAndBind(VkBuffer buffer, MemoryAllocationPrefered preference)
{
	VkMemoryRequirements memReq = {};
	vkGetBufferMemoryRequirements(device_->getDevice(), buffer, &memReq);

	auto mem = allocate(memReq.size, preference, memReq.memoryTypeBits);
	vkBindBufferMemory(device_->getDevice(), buffer, mem->getMemory(), 0);

	return mem;
}

std::shared_ptr<Memory> MemoryAllocator::allocateAndBind(VkImage image, MemoryAllocationPrefered preference)
{
	VkMemoryRequirements memReq = {};
	vkGetImageMemoryRequirements(device_->getDevice(), image, &memReq);

	auto mem = allocate(memReq.size, preference, memReq.memoryTypeBits);
	vkBindImageMemory(device_->getDevice(), image, mem->getMemory(), 0);

	return mem;
}

static int32_t findProperties(const VkPhysicalDeviceMemoryProperties* pMemoryProperties,
	uint32_t memoryTypeBitsRequirement,
	VkMemoryPropertyFlags requiredProperties)
{
	const uint32_t memoryCount = pMemoryProperties->memoryTypeCount;
	for (uint32_t memoryIndex = 0; memoryIndex < memoryCount; ++memoryIndex)
	{
		const uint32_t memoryTypeBits = (1 << memoryIndex);
		const bool isRequiredMemoryType = memoryTypeBitsRequirement & memoryTypeBits;
		const VkMemoryPropertyFlags properties =
			pMemoryProperties->memoryTypes[memoryIndex].propertyFlags;
		const bool hasRequiredProperties =
			(properties & requiredProperties) == requiredProperties;
		if (isRequiredMemoryType && hasRequiredProperties)
			return static_cast<int32_t>(memoryIndex);
	}
	// failed to find memory type
	return -1;
}

static std::vector<uint32_t> findProperties2(const VkPhysicalDeviceMemoryProperties* pMemoryProperties, uint32_t memoryTypeBitsRequirement, VkMemoryPropertyFlags requiredProperties)
{
	std::vector<uint32_t> vec;
	const uint32_t memoryCount = pMemoryProperties->memoryTypeCount;
	for (uint32_t memoryIndex = 0; memoryIndex < memoryCount; ++memoryIndex)
	{
		const uint32_t memoryTypeBits = (1 << memoryIndex);
		const bool isRequiredMemoryType = memoryTypeBitsRequirement & memoryTypeBits;
		const VkMemoryPropertyFlags properties =
			pMemoryProperties->memoryTypes[memoryIndex].propertyFlags;
		const bool hasRequiredProperties =
			(properties & requiredProperties) == requiredProperties;
		if (isRequiredMemoryType && hasRequiredProperties)
			vec.push_back(memoryIndex);
	}
	return std::move(vec);
}