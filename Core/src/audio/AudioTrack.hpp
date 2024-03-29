#pragma once

#include <memory>
#include <audio/IAudioTrack.hpp>
#include <vector>
#include <cstdint>

namespace CubA4::audio
{
	class IAudioSource;

	class AudioTrack :
		public virtual IAudioTrack
	{
	public:
		AudioTrack(std::unique_ptr<IAudioSource> source);
		~AudioTrack();

		void attachBuffer(std::shared_ptr<IAudioBuffer> buffer) override;
		void play() override;
		void stop() override;

		void setVolume(float volume) override;
		void setPosition(const CubA4::world::GlobalPosition &pos) override;
		void setVelocity(const CubA4::Vector3 &velocity) override;
	private:
		std::unique_ptr<IAudioSource> source_;
	};
}