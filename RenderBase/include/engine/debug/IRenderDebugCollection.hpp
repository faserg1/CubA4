#pragma once

#include <world/Position.hpp>
#include <base/Color.hpp>

namespace CubA4::render::engine::debug
{
	class IRenderDebugCollection
	{
	public:
		virtual ~IRenderDebugCollection() = default;

		virtual void addLine(CubA4::world::ChunkPos chPos, CubA4::world::BasePos<float> from, CubA4::world::BasePos<float> to,
			CubA4::ColorRGB color = {1, 0, 0}) = 0;
		virtual void hide() = 0;
		virtual void show() = 0;
		virtual bool isVisible() const = 0;
		virtual void toggleVisibility() = 0;
	protected:
		IRenderDebugCollection() = default;
	};
}