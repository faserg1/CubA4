#include <vulkan/Framebuffer.hpp>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::engine::memory;

Framebuffer::Framebuffer(std::shared_ptr<const Device> device, CubA4::render::engine::memory::MemoryAllocator &allocator,
    std::shared_ptr<FramebufferImage> framebufferImage, std::shared_ptr<FramebufferImage> depthImage, VkImage swapchainImage,
    VkRenderPass renderPass, VkCommandBuffer cmdBuffer) :
        device_(device), fence_(device), renderDoneSemaphore_(Semaphore::create(device)), cmdBuffer_(cmdBuffer),
        imagePresent_(swapchainImage), framebufferImage_(framebufferImage), depthImage_(depthImage),
        dirty_(true)
{

    if (!(imageView_ = createImageView(framebufferImage_->getImage(), framebufferImage_->getFormat(), VK_IMAGE_ASPECT_COLOR_BIT)))
        return;

    //create depth image view
    if (!(depthImageView_ = createImageView(depthImage_->getImage(), depthImage_->getFormat(), VK_IMAGE_ASPECT_DEPTH_BIT)))
        return;

    //create framebuffer

    // TODO: Info about attaches in common place?

    VkImageView attachments[] = { imageView_, depthImageView_};

    VkFramebufferCreateInfo framebufferCreateInfo = {};
    framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferCreateInfo.renderPass = renderPass;
    framebufferCreateInfo.attachmentCount = 2;
    framebufferCreateInfo.pAttachments = attachments;
    framebufferCreateInfo.layers = 1;
    framebufferCreateInfo.width = framebufferImage_->getSize().width;
    framebufferCreateInfo.height = framebufferImage_->getSize().height;

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

    //destroy depth image view
    vkDestroyImageView(device_->getDevice(), depthImageView_, nullptr);

    //destroy image view
    vkDestroyImageView(device_->getDevice(), imageView_, nullptr);
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

VkImage Framebuffer::getPresentImage() const
{
    return imagePresent_;
}

VkImage Framebuffer::getFramebufferImage() const
{
    return framebufferImage_->getImage();
}

std::shared_ptr<const Semaphore> Framebuffer::getRenderDoneSemaphore() const
{
    return renderDoneSemaphore_;
}

VkFence Framebuffer::getFence() const
{
    return fence_.getFence();
}

VkImageView Framebuffer::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspect)
{
    VkImageView view;

    VkImageViewCreateInfo imageViewCreateInfo = {};
    imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.image = image;
    imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageViewCreateInfo.format = format;
    imageViewCreateInfo.subresourceRange.aspectMask = aspect;
    imageViewCreateInfo.subresourceRange.layerCount = 1;
    imageViewCreateInfo.subresourceRange.levelCount = 1;
    
    if (vkCreateImageView(device_->getDevice(), &imageViewCreateInfo, nullptr, &view) != VK_SUCCESS)
    {
        //TODO: [OOKAMI] Exception, etc
        return VK_NULL_HANDLE;
    }

    return view;
}