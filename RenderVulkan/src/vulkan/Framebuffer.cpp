#include <vulkan/Framebuffer.hpp>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::engine::memory;

Framebuffer::Framebuffer(std::shared_ptr<const Device> device, CubA4::render::engine::memory::MemoryAllocator &allocator,
    VkImage swapchainImage, VkFormat format, uint32_t width, uint32_t height, VkRenderPass renderPass, VkCommandBuffer cmdBuffer) :
        device_(device), fence_(device), renderDoneSemaphore_(Semaphore::create(device)), cmdBuffer_(cmdBuffer), image_(swapchainImage), dirty_(true)
{
    VkImageViewCreateInfo imageViewCreateInfo = {};
    imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    imageViewCreateInfo.image = swapchainImage;
    imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    imageViewCreateInfo.format = format;
    imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    imageViewCreateInfo.subresourceRange.layerCount = 1;
    imageViewCreateInfo.subresourceRange.levelCount = 1;
    
    if (vkCreateImageView(device_->getDevice(), &imageViewCreateInfo, nullptr, &imageView_) != VK_SUCCESS)
    {
        //TODO: [OOKAMI] Exception, etc
        return;
    }

    // TODO: [OOKAMI] Хранить формат в едином месте
    VkImageCreateInfo depthInfo = {};
    depthInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    depthInfo.format = VK_FORMAT_D32_SFLOAT_S8_UINT;
    depthInfo.imageType = VK_IMAGE_TYPE_2D;
    depthInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depthInfo.samples = VK_SAMPLE_COUNT_1_BIT;
    depthInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
    depthInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    depthInfo.extent.width = width;
    depthInfo.extent.height = height;
    depthInfo.extent.depth = 1;
    depthInfo.arrayLayers = 1;
    depthInfo.mipLevels = 1;
    
    if (vkCreateImage(device_->getDevice(), &depthInfo, nullptr, &depthImage_) != VK_SUCCESS)
    {
        //TODO: [OOKAMI] Exception, etc
        return;
    }

    depthMemory_ = allocator.allocateAndBind(depthImage_, MemoryAllocationPrefered::Device);

    //create depth image view
    VkImageViewCreateInfo depthImageViewCreateInfo = {};
    depthImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    depthImageViewCreateInfo.image = depthImage_;
    depthImageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    depthImageViewCreateInfo.format = depthInfo.format;
    depthImageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
    depthImageViewCreateInfo.subresourceRange.layerCount = 1;
    depthImageViewCreateInfo.subresourceRange.levelCount = 1;

    if (vkCreateImageView(device_->getDevice(), &depthImageViewCreateInfo, nullptr, &depthImageView_) != VK_SUCCESS)
    {
        //TODO: [OOKAMI] Exception, etc
        return;
    }

    //create framebuffer

    // TODO: Info about attaches in common place?

    VkImageView attachments[] = { imageView_, depthImageView_};

    VkFramebufferCreateInfo framebufferCreateInfo = {};
    framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferCreateInfo.renderPass = renderPass;
    framebufferCreateInfo.attachmentCount = 2;
    framebufferCreateInfo.pAttachments = attachments;
    framebufferCreateInfo.layers = 1;
    framebufferCreateInfo.width = width;
    framebufferCreateInfo.height = height;

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

    //destroy depth image
    vkDestroyImage(device_->getDevice(), depthImage_, nullptr);

    //destroy depth image memory
    depthMemory_.reset();

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

std::shared_ptr<const Semaphore> Framebuffer::getRenderDoneSemaphore() const
{
    return renderDoneSemaphore_;
}

VkFence Framebuffer::getFence() const
{
    return fence_.getFence();
}