#pragma once

#include <memory>
#include <audio/IAudioManager.hpp>
#include <audio/AudioImporter.hpp>
#include <audio/AudioTrackManager.hpp>
#include <world/GlobalPosition.hpp>

namespace CubA4::audio
{
	class AudioTrack;
	class IAudioPlayer;

	class AudioManager : public virtual IAudioManager
	{
	public:
		AudioManager(std::shared_ptr<IAudioPlayer> player);

		IAudioImporter &getImporter() override;
		IAudioListener &getListener() override;
		IAudioTrackManager &getTrackManager() override;
	private:
		const std::shared_ptr<IAudioPlayer> player_;
		AudioImporter importer_;
		AudioTrackManager trackManager_;
	};
}