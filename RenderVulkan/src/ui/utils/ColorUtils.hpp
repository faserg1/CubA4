#pragma once

#include <skia/include/core/SkColorType.h>
#include <vulkan/vulkan.h>

constexpr SkColorType getColorType(VkFormat format)
{
	switch (format)
	{
	case VK_FORMAT_R8G8B8A8_SRGB:
		return kSRGBA_8888_SkColorType;
	case VK_FORMAT_B8G8R8A8_UNORM:
		return kBGRA_8888_SkColorType;
	}
	return SkColorType::kUnknown_SkColorType;
}