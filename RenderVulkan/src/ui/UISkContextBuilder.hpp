#pragma once

#include <memory>

#include <vulkan/Instance.hpp>
#include <vulkan/PhysicalDevice.hpp>
#include <vulkan/Device.hpp>
#include <ui/UISkContext.hpp>


namespace CubA4::ui
{
    class UISkContextBuilder
    {
    public:
        UISkContextBuilder(std::shared_ptr<CubA4::render::vulkan::Instance> instance,
            std::shared_ptr<CubA4::render::vulkan::PhysicalDevice> physDevice,
            std::shared_ptr<CubA4::render::vulkan::Device> device);

        std::shared_ptr<UISkContext> createContext();
    private:
        
    private:
        const std::shared_ptr<CubA4::render::vulkan::Instance> instance_;
        const std::shared_ptr<CubA4::render::vulkan::PhysicalDevice> physDevice_;
        const std::shared_ptr<CubA4::render::vulkan::Device> device_;
    };
}