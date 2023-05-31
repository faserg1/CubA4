#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <vulkan/Device.hpp>
#include <vulkan/Memory.hpp>

namespace CubA4::render::vulkan
{
	class FramebufferImage
	{
        using Memory = CubA4::render::vulkan::Memory;
	public:
        FramebufferImage(std::shared_ptr<const vulkan::Device> device, VkImage image, VkFormat format, VkExtent2D size, VkImageAspectFlags aspectFlags, std::shared_ptr<const Memory> memory = {});
        ~FramebufferImage();

        VkImage getImage() const;
        VkImageView getImageView() const;
        VkExtent2D getSize() const;
        VkFormat getFormat() const;
    private:
        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspect);
    private:
        const std::shared_ptr<const vulkan::Device> device_;
        VkImage image_;
        VkImageView imageView_;
        VkFormat format_;
        VkExtent2D size_;
        std::shared_ptr<const Memory> memory_;
    };
}