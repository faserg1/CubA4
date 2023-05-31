#pragma once

#include <ui/IUIManager.hpp>
#include <ui/UISkContext.hpp>
#include <vulkan/Instance.hpp>
#include <vulkan/Device.hpp>
#include <engine/memory/MemoryAllocator.hpp>
#include <memory>

namespace CubA4::render::ui
{
    class UIManager : public virtual IUIManager
    {
        struct UIFramebuffer
        {
            VkImage image;
            std::shared_ptr<const CubA4::render::vulkan::Memory> memory;
        };
    public:
        UIManager(std::shared_ptr<const CubA4::render::vulkan::Instance> instance,
            std::shared_ptr<const CubA4::render::vulkan::Device> device);
        ~UIManager();

        void initFramebuffer(VkFormat format, VkExtent2D resolution);
    private:
        static std::shared_ptr<UISkContext> createContext(std::shared_ptr<const CubA4::render::vulkan::Instance> instance,
            std::shared_ptr<const CubA4::render::vulkan::Device> device);
    private:
        const std::shared_ptr<const CubA4::render::vulkan::Instance> instance_;
        const std::shared_ptr<const CubA4::render::vulkan::Device> device_;
        const std::shared_ptr<UISkContext> context_;
        CubA4::render::engine::memory::MemoryAllocator allocator_;
        std::shared_ptr<UIFramebuffer> framebuffer_;

    };
}