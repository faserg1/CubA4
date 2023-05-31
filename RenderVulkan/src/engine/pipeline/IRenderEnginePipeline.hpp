#pragma once

#include <vector>
#include <memory>
#include <world/IChunk.hpp>
#include <engine/pipeline/RenderFramebufferData.hpp>

namespace CubA4::render::engine::pipeline
{
	class IRenderEnginePipeline
	{
	public:
		virtual void onFramebufferUpdated(const RenderFramebufferData &data) = 0;
	protected:
		explicit IRenderEnginePipeline() = default;
		virtual ~IRenderEnginePipeline() = default;
	private:
	};
}
