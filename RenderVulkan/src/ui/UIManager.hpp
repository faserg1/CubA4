#pragma once

#include <ui/IUIManager.hpp>
#include <ui/UISkContext.hpp>
#include <vulkan/Instance.hpp>
#include <vulkan/Device.hpp>
#include <vulkan/Swapchain.hpp>
#include <vulkan/Semaphore.hpp>
#include <memory>
#include <vector>

namespace CubA4::render::ui
{
	struct UIFramebuffer
	{
		sk_sp<SkSurface> surface;
		std::shared_ptr<CubA4::render::vulkan::Semaphore> renderDoneSemaphore;
	};

    class UIManager : public virtual IUIManager
    {
        
    public:
        UIManager(std::shared_ptr<const CubA4::render::vulkan::Instance> instance,
            std::shared_ptr<const CubA4::render::vulkan::Device> device);
        ~UIManager();

        void swapchainChanged(std::shared_ptr<const CubA4::render::vulkan::Swapchain> swapchain);
		const UIFramebuffer &getFramebuffer(uint32_t imageIdx) const;

		void drawOn(uint32_t imageIdx);

		void submit();
    private:
        static std::shared_ptr<UISkContext> createContext(std::shared_ptr<const CubA4::render::vulkan::Instance> instance,
            std::shared_ptr<const CubA4::render::vulkan::Device> device);
    private:
        const std::shared_ptr<const CubA4::render::vulkan::Instance> instance_;
        const std::shared_ptr<const CubA4::render::vulkan::Device> device_;
        const std::shared_ptr<UISkContext> context_;
        std::vector<UIFramebuffer> framebuffers_;

    };
}