#pragma once

#include <memory>
#include <vector>
#include <engine/world/RenderChunk.hpp>

namespace CubA4:: render::engine::pipeline
{
	class IRenderEnginePipelineSubscriber
	{
	public:
		virtual void chunksUpdated(std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderChunk>> renderChunks) = 0;
	protected:
		explicit IRenderEnginePipelineSubscriber() = default;
		virtual ~IRenderEnginePipelineSubscriber() = default;
	private:
	};
}
