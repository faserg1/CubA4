#pragma once

#include <cstdint>

namespace CubA4::render::engine::pipeline
{
	struct RenderChunkPipelineData
	{
		uint32_t width;
		uint32_t height;
		uint32_t subpass;

		friend constexpr bool operator==(const RenderChunkPipelineData &one, const RenderChunkPipelineData &two) = default;
		friend constexpr bool operator!=(const RenderChunkPipelineData &one, const RenderChunkPipelineData &two) = default;
	};
}
