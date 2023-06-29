#include <vulkan/FramebufferImage.hpp>
using namespace CubA4::render::vulkan;

FramebufferImage::FramebufferImage(std::shared_ptr<const vulkan::Device> device, VkImage image, VkFormat format, VkExtent2D size, VkImageAspectFlags aspectFlags, std::shared_ptr<const Memory> memory) :
    device_(device), image_(image), imageView_(createImageView(image, format, aspectFlags)),
	format_(format), aspectFlags_(aspectFlags), size_(size), memory_(memory)
{
}

FramebufferImage::~FramebufferImage()
{
    vkDestroyImageView(device_->getDevice(), imageView_, nullptr);
    if (memory_) // if we own that image
        vkDestroyImage(device_->getDevice(), image_, nullptr);
}

VkImage FramebufferImage::getImage() const
{
    return image_;
}

VkImageView FramebufferImage::getImageView() const
{
    return imageView_;
}

VkExtent2D FramebufferImage::getSize() const
{
    return size_;
}

VkFormat FramebufferImage::getFormat() const
{
    return format_;
}

VkImageAspectFlags FramebufferImage::getAspectFlags() const
{
	return aspectFlags_;
}

VkImageView FramebufferImage::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspect)
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