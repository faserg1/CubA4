#pragma once

#include <memory>
#include <engine/pipeline/IRenderEnginePipeline.hpp>

namespace CubA4::object
{
	struct Transform;
	struct WorldInfo;
	struct RenderInfoComponent;
}

namespace CubA4::render::engine::pipeline
{
	class IRenderEngineEntityPipeline : public virtual IRenderEnginePipeline
	{
	public:
		virtual void onEntityAdded(const CubA4::object::Transform &tr, const CubA4::object::WorldInfo &wi, const CubA4::object::RenderInfoComponent &render) = 0;
		virtual void onEntityUpdated(const CubA4::object::Transform &tr, const CubA4::object::WorldInfo &wi, const CubA4::object::RenderInfoComponent &render) = 0;
		virtual void onEntityRemoved(const CubA4::object::Transform &tr, const CubA4::object::WorldInfo &wi, const CubA4::object::RenderInfoComponent &render) = 0;
	protected:
		explicit IRenderEngineEntityPipeline() = default;
		virtual ~IRenderEngineEntityPipeline() = default;
	private:
	};
}
