#pragma once

#include <config/Enums.hpp>
#include <vulkan/vulkan.h>

namespace CubA4::render::vulkan::util
{
    constexpr VkSampleCountFlagBits convertAntialiasing(CubA4::render::config::AntiAliasing aa)
    {
        using AA = CubA4::render::config::AntiAliasing;
        switch (aa)
        {
            case AA::Disabled:
                return VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
            case AA::MSAA2:
                return VkSampleCountFlagBits::VK_SAMPLE_COUNT_2_BIT;
            case AA::MSAA4:
                return VkSampleCountFlagBits::VK_SAMPLE_COUNT_4_BIT;
            case AA::MSAA8:
                return VkSampleCountFlagBits::VK_SAMPLE_COUNT_8_BIT;
            case AA::MSAA16:
                return VkSampleCountFlagBits::VK_SAMPLE_COUNT_16_BIT;
            case AA::MSAA32:
                return VkSampleCountFlagBits::VK_SAMPLE_COUNT_32_BIT;
            case AA::MSAA64:
                return VkSampleCountFlagBits::VK_SAMPLE_COUNT_64_BIT;
        }
        return VK_SAMPLE_COUNT_1_BIT;
    }
}

