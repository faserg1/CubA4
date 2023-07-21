#pragma once

#include <ui/IRenderUIManager.hpp>
#include <ui/UISkContext.hpp>
#include <vulkan/Instance.hpp>
#include <vulkan/Device.hpp>
#include <vulkan/Swapchain.hpp>
#include <vulkan/Semaphore.hpp>
#include <memory>
#include <vector>

#include <ui/components/MainCanvas.hpp>
#include <ui/ComponentFactory.hpp>

namespace CubA4::render::ui
{
	struct UIFramebuffer
	{
		sk_sp<SkSurface> surface;
		std::shared_ptr<CubA4::render::vulkan::Semaphore> renderDoneSemaphore;
	};

    class UIManager : public virtual IRenderUIManager
    {
        
    public:
        UIManager(std::shared_ptr<const CubA4::render::vulkan::Instance> instance,
            std::shared_ptr<const CubA4::render::vulkan::Device> device);
        ~UIManager();

		std::shared_ptr<IComponentFactory> getComponentFactory() const override;
		std::shared_ptr<IMainCanvas> getMainCanvas() const override;

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

		std::shared_ptr<MainCanvas> mainCanvas_;
		std::shared_ptr<ComponentFactory> componentFactory_;
    };
}