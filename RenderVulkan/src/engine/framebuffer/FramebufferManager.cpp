#include <engine/framebuffer/FramebufferManager.hpp>
using namespace CubA4::render::engine;
using namespace CubA4::render::vulkan;

FramebufferManager::FramebufferManager(std::shared_ptr<const vulkan::Device> device, CubA4::render::config::VulkanConfigAdapter config) :
    device_(device), config_(config), commandPool_(device, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
{

}

void FramebufferManager::setRenderPass(std::shared_ptr<const vulkan::RenderPass> renderPass)
{
	renderPass_ = renderPass;
}

// Create framebuffers
// TODO: Make virtual
void FramebufferManager::onSwapchainUpdate(std::shared_ptr<const vulkan::Swapchain> swapchain)
{
	if (currentSwapchain_)
	{
		oldFramebuffers_.push_back(OldFramebufferInfo {
			.cyclesLeft = 10,
			.oldSwapchain = currentSwapchain_,
			.oldFramebuffers = framebuffers_,
		});
	}
	currentSwapchain_ = swapchain;

	onSwapchainUpdateInternal(swapchain);
	
	// TODO: assert attachmentsCount_ != 0
}

std::shared_ptr<CubA4::render::vulkan::Framebuffer> FramebufferManager::onAcquire(uint32_t imgIndex)
{
	if (imgIndex == 0)
	{
		onCycle();
	}
	auto framebuffer = framebuffers_[imgIndex];
	framebuffer->onAquired();
	return framebuffer;
}

std::shared_ptr<CubA4::render::vulkan::Framebuffer> FramebufferManager::get(uint32_t imgIndex) const
{
	return framebuffers_[imgIndex];
}

void FramebufferManager::onAcquireFailed()
{
	onCycle();
}

void FramebufferManager::markDirty()
{
	for (auto &framebuffer : framebuffers_)
	{
		framebuffer->markDirty();
	}
}

VkExtent2D FramebufferManager::getExtent() const
{
	return currentSwapchain_->getResolution();
}

uint32_t FramebufferManager::getImageCount() const
{
	return currentSwapchain_->getImageCount();
}

uint32_t FramebufferManager::getAttachmentsCount() const
{
	return attachmentsCount_;
}

void FramebufferManager::onCycle()
{
	auto locker = oldFramebuffersLock_.lock();
	auto it = std::remove_if(oldFramebuffers_.begin(), oldFramebuffers_.end(), [](OldFramebufferInfo &oldInfo) -> bool
	{
		if (oldInfo.cyclesLeft > 0)
			oldInfo.cyclesLeft--;
		return !oldInfo.cyclesLeft;
	});
	oldFramebuffers_.erase(it, oldFramebuffers_.end());
}