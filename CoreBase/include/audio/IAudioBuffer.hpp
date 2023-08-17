#pragma once

#include <cstdint>

namespace CubA4::audio
{
	class IAudioBuffer
	{
	public:
		virtual ~IAudioBuffer() = default;

		/// @brief Filling stereo data, should be in interleaved format (LRLRLR...), left channel first
		/// @param data 8-bit PCM data is expressed as an unsigned value over the range 0 to 255, 128 being an audio output level of zero.
		/// @param samplesCount samples count
		/// @param rate Frequency, in Hz
		virtual void fillDataStereo(uint8_t *data, size_t samplesCount, uint32_t rate) = 0;

		/// @brief Filling stereo data, should be in interleaved format (LRLRLR...), left channel first
		/// @param data 16-bit PCM data is expressed as a signed value over the range -32768 to 32767, 0 being an audio output level of zero
		/// @param samplesCount samples count
		/// @param rate Frequency, in Hz
		virtual void fillDataStereo(int16_t *data, size_t samplesCount, uint32_t rate) = 0;

		/// @brief Filling mono data
		/// @param data 8-bit PCM data is expressed as an unsigned value over the range 0 to 255, 128 being an audio output level of zero.
		/// @param samplesCount samples count
		/// @param rate Frequency, in Hz
		virtual void fillDataMono(uint8_t *data, size_t samplesCount, uint32_t rate) = 0;

		/// @brief Filling mono data
		/// @param data 16-bit PCM data is expressed as a signed value over the range -32768 to 32767, 0 being an audio output level of zero
		/// @param samplesCount samples count
		/// @param rate Frequency, in Hz
		virtual void fillDataMono(int16_t *data, size_t samplesCount, uint32_t rate) = 0;
	protected:
		IAudioBuffer() = default;
	};
}