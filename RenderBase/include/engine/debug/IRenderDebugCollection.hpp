#pragma once

#include <world/Position.hpp>

namespace CubA4::render::engine::debug
{
	class IRenderDebugCollection
	{
	public:
		virtual ~IRenderDebugCollection() = default;

		virtual void addLine(CubA4::world::ChunkPos chPos, CubA4::world::BasePos<float> from, CubA4::world::BasePos<float> to) = 0;
		virtual void hide() = 0;
		virtual void show() = 0;
		virtual bool isVisible() const = 0;
		virtual void toggleVisibility() = 0;
	protected:
		IRenderDebugCollection() = default;
	};
}