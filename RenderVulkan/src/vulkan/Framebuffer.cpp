#include <vulkan/Framebuffer.hpp>
#include <vector>
#include <algorithm>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::engine::memory;

Framebuffer::Framebuffer(std::shared_ptr<const Device> device,
    std::vector<std::shared_ptr<FramebufferImage>> attachments,
    VkRenderPass renderPass, VkCommandBuffer cmdBuffer) :
        device_(device), fence_(device), renderDoneSemaphore_(Semaphore::create(device)), cmdBuffer_(cmdBuffer),
        attachments_(attachments),
        dirty_(true)
{
    std::vector<VkImageView> viewAttachments(attachments_.size());

	device_->getMarker().setName(renderDoneSemaphore_->getSemaphore(), "[Framebuffer] renderDoneSemaphore");

    std::transform(attachments_.begin(), attachments_.end(), viewAttachments.begin(), [](std::shared_ptr<FramebufferImage> framebufferImage) -> VkImageView
    {
        return framebufferImage->getImageView();
    });


    VkFramebufferCreateInfo framebufferCreateInfo = {};
    framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferCreateInfo.renderPass = renderPass;
    framebufferCreateInfo.attachmentCount = static_cast<decltype(framebufferCreateInfo.attachmentCount)>(viewAttachments.size());
    framebufferCreateInfo.pAttachments = viewAttachments.data();
    framebufferCreateInfo.layers = 1;
    // TODO: Think about different sizes
    framebufferCreateInfo.width = attachments.front()->getSize().width;
    framebufferCreateInfo.height = attachments.front()->getSize().height;

    if (vkCreateFramebuffer(device_->getDevice(), &framebufferCreateInfo, nullptr, &framebuffer_) != VK_SUCCESS)
    {
        //TODO: [OOKAMI] Exception, etc
        return;
    }

    state_.store(FramebufferState::Free);
}

Framebuffer::~Framebuffer()
{
    // No need to wait - they MUST be destroyed after no usage for sure
	vkDestroyFramebuffer(device_->getDevice(), framebuffer_, nullptr);
}

FramebufferState Framebuffer::getState() const
{
    return state_.load();
}

bool Framebuffer::waitFence()
{
    return fence_.wait(50) == VK_SUCCESS;
}

void Framebuffer::resetFence()
{
    fence_.reset();
}

void Framebuffer::onAquired()
{
    state_.store(FramebufferState::Acquired);
}

void Framebuffer::onRecorded()
{
    dirty_.store(false);
    recordAwait_.store(false);
    recorded_.store(true);
}

void Framebuffer::onSend()
{
    state_.store(FramebufferState::Pending);
}

void Framebuffer::markDirty()
{
    dirty_.store(true);
}

bool Framebuffer::isDirty() const
{
    return dirty_.load();
}

bool Framebuffer::isRecorded() const
{
    return recorded_.load();
}

void Framebuffer::onRecordAwait()
{
    recordAwait_.store(true);
    recorded_.store(false);
}

bool Framebuffer::isRecordAwait() const
{
    return recordAwait_.load();
}

VkCommandBuffer Framebuffer::getCommandBuffer() const
{
    return cmdBuffer_;
}

VkFramebuffer Framebuffer::getFrameBuffer() const
{
    return framebuffer_;
}

uint32_t Framebuffer::getAttachmentsCount() const
{
	return static_cast<uint32_t>(attachments_.size());
}

FramebufferImage &Framebuffer::getFrameBufferImage(uint32_t attachmentIndex) const
{
	return *attachments_[attachmentIndex];
}

std::shared_ptr<const Semaphore> Framebuffer::getRenderDoneSemaphore() const
{
    return renderDoneSemaphore_;
}

VkFence Framebuffer::getFence() const
{
    return fence_.getFence();
}
