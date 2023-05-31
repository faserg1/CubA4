#pragma once

#include <vulkan/vulkan.h>
#include <vulkan/Device.hpp>
#include <vulkan/Memory.hpp>
#include <vulkan/Fence.hpp>
#include <vulkan/Semaphore.hpp>
#include <engine/memory/MemoryAllocator.hpp>
#include <vulkan/FramebufferImage.hpp>
#include <vector>
#include <memory>
#include <atomic>

namespace CubA4::render::vulkan
{
	enum class FramebufferState : uint32_t
	{
		Invalid,
		Free,
		Acquired,
		Pending
	};

	class Framebuffer
	{
	public:
		explicit Framebuffer(std::shared_ptr<const Device> device, std::vector<std::shared_ptr<FramebufferImage>> attachments,
			VkRenderPass renderPass, VkCommandBuffer cmdBuffer);
		~Framebuffer();

		FramebufferState getState() const;

		bool waitFence();
		void resetFence();
		
		void onAquired();
		void onRecorded();
		void onSend();

		void markDirty();
		bool isDirty() const;
		bool isRecorded() const;

		void onRecordAwait();
		bool isRecordAwait() const;

		VkCommandBuffer getCommandBuffer() const;
		VkFramebuffer getFrameBuffer() const;
		std::shared_ptr<const Semaphore> getRenderDoneSemaphore() const;
		VkFence getFence() const;
	private:
		const std::shared_ptr<const Device> device_;
		Fence fence_;
		std::shared_ptr<const Semaphore> renderDoneSemaphore_;
		VkCommandBuffer cmdBuffer_;

		VkFramebuffer framebuffer_;

		std::vector<std::shared_ptr<FramebufferImage>> attachments_;

		std::atomic_bool dirty_;
		std::atomic_bool recordAwait_;
		std::atomic_bool recorded_;
		std::atomic<FramebufferState> state_;
	};
}
