#pragma once

#include <memory>
#include <engine/world/RenderChunk.hpp>

namespace CubA4:: render::engine::pipeline
{
	class IRenderEnginePipelineSubscriber
	{
	public:
		virtual void chunkCompiled(std::shared_ptr<const CubA4::render::engine::world::RenderChunk> renderChunk) = 0;
	protected:
		explicit IRenderEnginePipelineSubscriber() = default;
		virtual ~IRenderEnginePipelineSubscriber() = default;
	private:
	};
}
