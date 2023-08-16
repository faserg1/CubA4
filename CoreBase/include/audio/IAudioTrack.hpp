#pragma once

#include <vector>
#include <cstdint>

namespace CubA4::audio
{
	class IAudioTrack
	{
	public:
		virtual ~IAudioTrack() = default;

		virtual const std::vector<int16_t> &getSamples() const = 0;
		virtual uint32_t getRate() const = 0;
	protected:
		IAudioTrack() = default;
	};
}