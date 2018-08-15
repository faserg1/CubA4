#include "./MemoryAllocator.hpp"
#include "../vulkan/Device.hpp"
#include "../vulkan/Memory.hpp"
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

static int32_t findProperties(const VkPhysicalDeviceMemoryProperties* pMemoryProperties, uint32_t memoryTypeBitsRequirement, VkMemoryPropertyFlags requiredProperties);

MemoryAllocator::MemoryAllocator(std::shared_ptr<const Device> device) :
	device_(device)
{
	
}

MemoryAllocator::~MemoryAllocator()
{
	
}

std::shared_ptr<Memory> MemoryAllocator::allocate(size_t size, MemoryAllocationPrefered preference, uint32_t supportedTypes)
{
	VkDeviceMemory memory;
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
		break;
	}
	int32_t index = findProperties(&props, supportedTypes, requiredFlags);
	if (index < 0)
		//TODO: [OOKAMI] Throw exception
		return {};
	info.memoryTypeIndex = static_cast<uint32_t>(index);
	if (vkAllocateMemory(device_->getDevice(), &info, nullptr, &memory) != VK_SUCCESS)
		return {};
	return Memory::create(device_, memory, info.allocationSize, props.memoryTypes[info.memoryTypeIndex].propertyFlags);
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