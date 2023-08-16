#pragma once

#include <memory>
#include <audio/IAudioManager.hpp>
#include <world/GlobalPosition.hpp>

namespace CubA4::audio
{
	class AudioTrack;
	class IAudioPlayer;

	class AudioManager : public virtual IAudioManager
	{
	public:
		AudioManager(std::shared_ptr<IAudioPlayer> player);
		std::shared_ptr<IAudioTrack> createTrack(std::shared_ptr<const CubA4::resources::IResource> resource) override;

		void play(std::shared_ptr<IAudioTrack> track, const CubA4::world::GlobalPosition &pos) override;
	private:
		std::shared_ptr<AudioTrack> createFromOgg(std::shared_ptr<const CubA4::resources::IResource> resource);

	private:
		const std::shared_ptr<IAudioPlayer> player_;
	};
}