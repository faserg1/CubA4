#pragma once

#include <audio/IAudioListener.hpp>

namespace CubA4::audio
{
	class AudioListener : public virtual IAudioListener
	{
	public:
		AudioListener();
		~AudioListener();

		void init();
		void setPosition(const CubA4::world::GlobalPosition &pos) override;
	};
}