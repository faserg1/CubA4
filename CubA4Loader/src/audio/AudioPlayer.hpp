#pragma once

#include <memory>
#include <audio/IAudioPlayer.hpp>

namespace CubA4::audio
{
	class AudioPlayer : public virtual IAudioPlayer
	{
		struct Data;
	public:
		AudioPlayer();
		~AudioPlayer();

		void play(std::shared_ptr<const IAudioTrack> track, const CubA4::world::GlobalPosition &pos) override;
		void setListenerPosition(const CubA4::world::GlobalPosition &pos) override;
	private:
		std::unique_ptr<Data> data_;
	};
}