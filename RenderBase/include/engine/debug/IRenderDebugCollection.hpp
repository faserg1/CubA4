#pragma once

#include <world/Position.hpp>
#include <base/Color.hpp>
#include <vector>

namespace CubA4::render::engine::debug
{
	struct LineInfo
	{
		CubA4::world::BasePos<float> from;
		CubA4::world::BasePos<float> to;
		CubA4::ColorRGB colorFrom;
		CubA4::ColorRGB colorTo;
	};

	class IRenderDebugCollection
	{
	public:
		virtual ~IRenderDebugCollection() = default;

		virtual void addLine(CubA4::world::ChunkPos chPos, CubA4::world::BasePos<float> from, CubA4::world::BasePos<float> to,
			CubA4::ColorRGB colorFrom, CubA4::ColorRGB colorTo) = 0;

		virtual void addCube(CubA4::world::ChunkPos chPos, CubA4::world::BasePos<float> at, float size = 1.f, CubA4::ColorRGB color = {1.f, 0.f, 0.f}) = 0;
		void addLine(CubA4::world::ChunkPos chPos, CubA4::world::BasePos<float> from, CubA4::world::BasePos<float> to,
			CubA4::ColorRGB color = {1.f, 0.f, 0.f})
		{
			addLine(chPos, from, to, color, color);
		}

		virtual void addLines(CubA4::world::ChunkPos chPos, const std::vector<LineInfo> &lines) = 0;
		
		virtual void clear() = 0;

		virtual void hide() = 0;
		virtual void show() = 0;
		virtual bool isVisible() const = 0;
		virtual void toggleVisibility() = 0;
	protected:
		IRenderDebugCollection() = default;
	};
}