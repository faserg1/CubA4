#include <engine/FramebufferManager.hpp>
using namespace CubA4::render::engine;

FramebufferManager::FramebufferManager(std::shared_ptr<const vulkan::Device> device, CubA4::render::config::VulkanConfigAdapter config) :
    device_(device), config_(config), builder_(device, config)
{

}

// Create framebuffers
void FramebufferManager::onSwapchainUpdate(std::shared_ptr<const vulkan::Swapchain> swapchain, std::shared_ptr<const vulkan::RenderPass> renderPass)
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
	framebuffers_ = builder_.createFramebuffers(swapchain, renderPass);
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