#pragma once

#include <object/components/Transform.hpp>
#include <object/components/WorldInfo.hpp>
#include <object/components/RenderInfoComponent.hpp>

namespace CubA4::render::engine::pipeline
{
	class IRenderEntitySubscriber
	{
	public:
		virtual ~IRenderEntitySubscriber() {}

		virtual void onEntityAdded(CubA4::object::Transform &tr, CubA4::object::WorldInfo &wi, CubA4::object::RenderInfoComponent &render) = 0;
		virtual void onEntityUpdated(CubA4::object::Transform &tr, CubA4::object::WorldInfo &wi, CubA4::object::RenderInfoComponent &render) = 0;
		virtual void onEntityRemoved(CubA4::object::Transform &tr, CubA4::object::WorldInfo &wi, CubA4::object::RenderInfoComponent &render) = 0;
	protected:
		IRenderEntitySubscriber() {}
	};
}