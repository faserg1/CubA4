#pragma once

#include <vector>
#include <memory>
#include <world/IChunk.hpp>
#include <engine/pipeline/IRenderEnginePipeline.hpp>

namespace CubA4::render::engine::pipeline
{
	class IRenderEngineWorldPipeline : public virtual IRenderEnginePipeline
	{
	public:
		virtual void pushChunks(std::vector<std::shared_ptr<const CubA4::world::IChunk>> chunks) = 0;
	protected:
		explicit IRenderEngineWorldPipeline() = default;
		virtual ~IRenderEngineWorldPipeline() = default;
	private:
	};
}
