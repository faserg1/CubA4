#pragma once

#include <audio/IAudioPool.hpp>
#include <audio/IAudioBuffer.hpp>
#include <cstdint>
#include <memory>

namespace CubA4::audio
{
	class AudioBuffer : public virtual IAudioBuffer
	{
		using IdType = uint32_t;
	public:
		AudioBuffer(IdType buffferId, std::shared_ptr<IAudioPool> pool);
		~AudioBuffer();
		void fillDataStereo(uint8_t *data, size_t samplesCount, uint32_t rate) override;
		void fillDataStereo(int16_t *data, size_t samplesCount, uint32_t rate) override;
		void fillDataMono(uint8_t *data, size_t samplesCount, uint32_t rate) override;
		void fillDataMono(int16_t *data, size_t samplesCount, uint32_t rate) override;

		IdType getBufferId() const;
	private:
		const IdType buffferId_;
		const std::weak_ptr<IAudioPool> pool_;
	};
}