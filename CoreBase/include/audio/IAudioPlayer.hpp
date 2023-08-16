#pragma once

#include <memory>
#include <world/GlobalPosition.hpp>

namespace CubA4::audio
{
	class IAudioTrack;

	class IAudioPlayer
	{
	public:
		virtual void play(std::shared_ptr<const IAudioTrack> track, const CubA4::world::GlobalPosition &pos) = 0;
		virtual void setListenerPosition(const CubA4::world::GlobalPosition &pos) = 0;
	protected:
		IAudioPlayer() = default;
	};
}