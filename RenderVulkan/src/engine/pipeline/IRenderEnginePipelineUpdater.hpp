#pragma once

#include <vector>
#include <memory>
#include <world/IChunk.hpp>

namespace CubA4::render::engine::pipeline
{
	class IRenderEnginePipelineUpdater
	{
	public:
		virtual void pushChunks(std::vector<std::shared_ptr<const CubA4::world::IChunk>> chunks) = 0;
	protected:
		explicit IRenderEnginePipelineUpdater() = default;
		virtual ~IRenderEnginePipelineUpdater() = default;
	private:
	};
}
