#pragma once

#include <cstdint>

namespace CubA4::render::engine::pipeline
{
	struct RenderFramebufferData
	{
		uint32_t width;
		uint32_t height;

		friend constexpr bool operator==(const RenderFramebufferData &one, const RenderFramebufferData &two) = default;
		friend constexpr bool operator!=(const RenderFramebufferData &one, const RenderFramebufferData &two) = default;
	};
}
