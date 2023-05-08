#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <vulkan/Device.hpp>
#include <engine/memory/IMemoryPart.hpp>

namespace CubA4::render::vulkan
{
	class FramebufferImage
	{
        using IMemoryPart = CubA4::render::engine::memory::IMemoryPart;
	public:
        FramebufferImage(std::shared_ptr<const vulkan::Device> device, VkImage image, VkFormat format, VkExtent2D size, std::shared_ptr<const IMemoryPart> memory);
        ~FramebufferImage();

        VkImage getImage() const;
        VkExtent2D getSize() const;
        VkFormat getFormat() const;
    private:
        const std::shared_ptr<const vulkan::Device> device_;
        VkImage image_;
        VkFormat format_;
        VkExtent2D size_;
        std::shared_ptr<const IMemoryPart> memoryPart_;
    };
}