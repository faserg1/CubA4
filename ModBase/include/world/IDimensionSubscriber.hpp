#pragma once

namespace CubA4::world
{
	class IDimensionSubscriber
	{
	public:
		virtual void onActiveChunksUpdated() {}
		virtual void onLoadedChunksUpdated() {}
	protected:
		explicit IDimensionSubscriber() = default;
		virtual ~IDimensionSubscriber() = default;
	};
}
