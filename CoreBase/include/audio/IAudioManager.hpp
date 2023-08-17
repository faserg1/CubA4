#pragma once

#include <memory>

namespace CubA4::audio
{
	class IAudioImporter;
	class IAudioListener;
	class IAudioTrackManager;

	class IAudioManager
	{
	public:
		virtual IAudioImporter &getImporter() = 0;
		virtual IAudioListener &getListener() = 0;
		virtual IAudioTrackManager &getTrackManager() = 0;
	protected:
		IAudioManager() = default;
	};
}