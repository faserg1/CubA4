#include <vulkan/FramebufferImage.hpp>
using namespace CubA4::render::vulkan;

FramebufferImage::FramebufferImage(std::shared_ptr<const vulkan::Device> device, VkImage image, VkFormat format, VkExtent2D size, std::shared_ptr<const IMemoryPart> memory) :
    device_(device), image_(image), format_(format), size_(size), memoryPart_(memory)
{

}

FramebufferImage::~FramebufferImage()
{
    if (memoryPart_) // if we own that image
        vkDestroyImage(device_->getDevice(), image_, nullptr);
}

VkImage FramebufferImage::getImage() const
{
    return image_;
}

VkExtent2D FramebufferImage::getSize() const
{
    return size_;
}

VkFormat FramebufferImage::getFormat() const
{
    return format_;
}