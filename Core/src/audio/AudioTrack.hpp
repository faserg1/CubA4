#pragma once

#include <audio/IAudioTrack.hpp>
#include <vector>
#include <cstdint>

namespace CubA4::audio
{
	class AudioTrack : public virtual IAudioTrack
	{
	public:
		AudioTrack(std::vector<int16_t> samples, uint32_t rate);

		const std::vector<int16_t> &getSamples() const override;
		uint32_t getRate() const override;
	private:
		const std::vector<int16_t> samples_;
		const uint32_t rate_;
	};
}