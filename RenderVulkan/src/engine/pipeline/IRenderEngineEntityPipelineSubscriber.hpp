#pragma once

#include <memory>
#include <vector>

namespace CubA4::render::engine::world
{
	class RenderEntity;
}

namespace CubA4::render::engine::pipeline
{
	class IRenderEngineEntityPipelineSubscriber
	{
	public:
		virtual void onRenderEntitiesUpdated(const std::vector<std::shared_ptr<const CubA4::render::engine::world::RenderEntity>> &entities) = 0;
	protected:
		explicit IRenderEngineEntityPipelineSubscriber() = default;
		virtual ~IRenderEngineEntityPipelineSubscriber() = default;
	private:
	};
}
