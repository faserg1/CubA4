#include "./MemoryManager.hpp"
#include "./MemoryAllocator.hpp"
#include "../vulkan/Device.hpp"
#include "../vulkan/Memory.hpp"
#include <list>
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

namespace
{
	uint64_t calcAlign(uint64_t size, uint64_t align)
	{
		if (!size)
			return 0;
		auto res = size % align;
		if (res == 0)
			return size;
		return size + align - res;
	}
}

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			class MemoryBlock;
			class MemoryPart;

			class MemoryBlock :
				public std::enable_shared_from_this<MemoryBlock>,
				public virtual IMemoryBlock
			{
			public:
				MemoryBlock(std::shared_ptr<Memory> memory);
				VkMemoryPropertyFlags getFlags() const override;
				uint32_t getMemoryTypeIndex() const override;
				std::shared_ptr<Memory> getMemory() const;
				std::shared_ptr<MemoryPart> allocatePart(uint64_t size, uint64_t alignment);
				void freePart(const MemoryPart *part);
			private:
				std::shared_ptr<Memory> memory_;
				std::list<std::weak_ptr<MemoryPart>> parts_;
			};

			class MemoryPart :
				public virtual IMemoryPart
			{
			public:
				MemoryPart(std::shared_ptr<MemoryBlock> block, VkDeviceSize offset, VkDeviceSize size);
				~MemoryPart();
				std::shared_ptr<Memory> getMemory() const override;
				VkDeviceSize getOffset() const override;
				VkDeviceSize getSize() const override;
				std::shared_ptr<const IMemoryBlock> getBlock() const override;
			private:
				const std::shared_ptr<MemoryBlock> block_;
				const VkDeviceSize offset_;
				const VkDeviceSize size_;
			};
		}
	}
}

MemoryBlock::MemoryBlock(std::shared_ptr<Memory> memory) :
	memory_(memory)
{

}

VkMemoryPropertyFlags MemoryBlock::getFlags() const
{
	return memory_->getFlags();
}

uint32_t MemoryBlock::getMemoryTypeIndex() const
{
	return memory_->getMemoryTypeIndex();
}

std::shared_ptr<Memory> MemoryBlock::getMemory() const
{
	return memory_;
}

std::shared_ptr<MemoryPart> MemoryBlock::allocatePart(uint64_t size, uint64_t alignment)
{
	if (!parts_.size())
	{
		auto part = std::make_shared<MemoryPart>(shared_from_this(), 0, size);
		parts_.push_back(part);
		return part;
	}
	VkDeviceSize lastOffset = 0;
	auto partIterator = parts_.begin();
	for (auto part : parts_)
	{
		auto locked = part.lock();
		auto partOffset = locked->getOffset();
		auto lastOffsetTemp = lastOffset;
		lastOffset = locked->getOffset() + locked->getSize();

		if (calcAlign(lastOffsetTemp, alignment) + size <= partOffset)
		{
			auto offset = calcAlign(lastOffsetTemp, alignment);
			auto part = std::make_shared<MemoryPart>(shared_from_this(), offset, size);
			parts_.insert(partIterator, part);
			return part;
		}
		partIterator++;
	}
	if (calcAlign(lastOffset, alignment) + size <= memory_->getSize())
	{
		auto offset = calcAlign(lastOffset, alignment);
		auto part = std::make_shared<MemoryPart>(shared_from_this(), offset, size);
		parts_.push_back(part);
		return part;
	}
	return {};
}

void MemoryBlock::freePart(const MemoryPart *part)
{
	parts_.remove_if([part](std::weak_ptr<MemoryPart> value) -> bool
	{
		auto locked = value.lock();
		if (!locked)
			return true;
		return locked->getOffset() == part->getOffset() && locked->getSize() == part->getSize();
	});
}


MemoryPart::MemoryPart(std::shared_ptr<MemoryBlock> block, VkDeviceSize offset, VkDeviceSize size) :
	block_(block), offset_(offset), size_(size)
{
}

MemoryPart::~MemoryPart()
{
	block_->freePart(this);
}

std::shared_ptr<Memory> MemoryPart::getMemory() const
{
	return block_->getMemory();
}

VkDeviceSize MemoryPart::getOffset() const
{
	return offset_;
}

VkDeviceSize MemoryPart::getSize() const
{
	return size_;
}

std::shared_ptr<const IMemoryBlock> MemoryPart::getBlock() const
{
	return block_;
}


MemoryManager::MemoryManager(std::shared_ptr<const Device> device, uint32_t blockSize) :
	device_(device), allocator_(std::make_shared<MemoryAllocator>(device)), blockSize_(blockSize)
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
	vkCreateCommandPool(device->getDevice(), &poolInfo, nullptr, &transitPool_);
}

MemoryManager::~MemoryManager()
{
	vkDestroyCommandPool(device_->getDevice(), transitPool_, nullptr);
}

std::shared_future<bool> MemoryManager::copyBufferToBuffer(VkBuffer src, VkBuffer dst, VkDeviceSize size)
{
	VkCommandBuffer copyCmd;
	VkFence bufferCopyDone;
	if (!allocateCmdBuffer(copyCmd, bufferCopyDone))
	{
		return {};
	}

	device_->getMarker().setName(bufferCopyDone, "Fence buffer copy awaiter");
	device_->getMarker().setName(copyCmd, "Command buffer for copy buffer");

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	vkBeginCommandBuffer(copyCmd, &beginInfo);
	VkBufferCopy region = {};
	region.dstOffset = 0;
	region.srcOffset = 0;
	region.size = size;
	vkCmdCopyBuffer(copyCmd, src, dst, 1, &region);
	vkEndCommandBuffer(copyCmd);

	return submitCmdBuffer(copyCmd, bufferCopyDone);
}

std::shared_future<bool> MemoryManager::updateBuffer(void *data, VkBuffer dst, VkDeviceSize offset, VkDeviceSize size, BufferBarrierType bufferBarrierType)
{
	VkCommandBuffer updateCmd;
	VkFence bufferUpdateDone;
	if (!allocateCmdBuffer(updateCmd, bufferUpdateDone))
	{
		return {};
	}

	device_->getMarker().setName(bufferUpdateDone, "Fence buffer update awaiter");
	device_->getMarker().setName(updateCmd, "Command buffer for update buffer");

	// TODO: [OOKAMI] Барьер скорее всего нужен только на выход, чтобы была видна запись.

	VkBufferMemoryBarrier bufferBarier = {};
	bufferBarier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
	bufferBarier.buffer = dst;
	bufferBarier.size = size;
	bufferBarier.offset = offset;

	auto &in = bufferBarier, out = bufferBarier;
	VkPipelineStageFlags outFlags = {};

	in.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	out.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	
	switch (bufferBarrierType)
	{
	case CubA4::render::engine::BufferBarrierType::Vertex:
		in.srcAccessMask = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
		out.dstAccessMask = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT;
		outFlags = VK_PIPELINE_STAGE_VERTEX_INPUT_BIT;
		break;
	case CubA4::render::engine::BufferBarrierType::Uniform:
		in.srcAccessMask = VK_ACCESS_UNIFORM_READ_BIT;
		out.dstAccessMask = VK_ACCESS_UNIFORM_READ_BIT;
		outFlags = VK_PIPELINE_STAGE_VERTEX_SHADER_BIT | VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT; // before the all shaders stages
		break;
	default:
		break;
	}

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	vkBeginCommandBuffer(updateCmd, &beginInfo);
	if (bufferBarrierType != BufferBarrierType::None)
	{
		/*vkCmdPipelineBarrier(updateCmd, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
			0, nullptr,
			1, &in,
			0, nullptr);*/
	}
	vkCmdUpdateBuffer(updateCmd, dst, offset, size, data);
	if (bufferBarrierType != BufferBarrierType::None)
	{
		vkCmdPipelineBarrier(updateCmd, VK_PIPELINE_STAGE_TRANSFER_BIT, outFlags, 0,
			0, nullptr,
			1, &out,
			0, nullptr);
	}
		
	vkEndCommandBuffer(updateCmd);

	return submitCmdBuffer(updateCmd, bufferUpdateDone);
}

uint32_t MemoryManager::calcAlign(uint32_t size, uint32_t align)
{
	return static_cast<uint32_t>(::calcAlign(size, align));
}

std::shared_ptr<const IMemoryPart> MemoryManager::allocatePart(uint64_t size, uint64_t alignment, uint32_t supportedTypes)
{
	if (size > blockSize_)
		return {};
	for (auto block : memoryBlocks_)
	{
		const uint32_t memoryTypeBits = (1 << block->getMemoryTypeIndex());
		const bool isRequiredMemoryType = supportedTypes & memoryTypeBits;
		if (!isRequiredMemoryType)
			continue;
		auto memBlock = std::dynamic_pointer_cast<MemoryBlock>(block);
		auto part = memBlock->allocatePart(size, alignment);
		if (!part)
			continue;
		return part;
	}
	auto newBlock = allocateBlock(supportedTypes);
	memoryBlocks_.push_back(newBlock);
	auto newMemBlock = std::dynamic_pointer_cast<MemoryBlock>(newBlock);
	return newMemBlock->allocatePart(size, alignment);
}

bool MemoryManager::allocateCmdBuffer(VkCommandBuffer &cmdBuffer, VkFence &fence)
{
	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	if (vkCreateFence(device_->getDevice(), &fenceInfo, nullptr, &fence) != VK_SUCCESS)
		return false;
	
	VkCommandBufferAllocateInfo allocateInfo = {};
	allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocateInfo.commandPool = transitPool_;
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocateInfo.commandBufferCount = 1;
	if (vkAllocateCommandBuffers(device_->getDevice(), &allocateInfo, &cmdBuffer) != VK_SUCCESS)
	{
		vkDestroyFence(device_->getDevice(), fence, nullptr);
		return false;
	}
	return true;
}

std::shared_future<bool> MemoryManager::submitCmdBuffer(VkCommandBuffer cmdBuffer, VkFence fence)
{
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &cmdBuffer;
	auto q = device_->getQueue(QueueType::Transmit);
	vkQueueSubmit(q->get(), 1, &submitInfo, fence);

	return std::async(std::launch::async, [=]() -> bool
	{
		bool result = false;
		if (vkWaitForFences(device_->getDevice(), 1, &fence, VK_TRUE, VK_WHOLE_SIZE) == VK_SUCCESS)
			result = true;
		vkDestroyFence(device_->getDevice(), fence, nullptr);
		vkFreeCommandBuffers(device_->getDevice(), transitPool_, 1, &cmdBuffer);
		return result;
	}).share();
}

std::shared_ptr<IMemoryBlock> MemoryManager::allocateBlock(uint32_t supportedTypes)
{
	auto memory = allocator_->allocate(blockSize_, MemoryAllocationPrefered::Device, supportedTypes);
	if (!memory)
		return {};
	return std::make_shared<MemoryBlock>(memory);
}