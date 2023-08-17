#pragma once

#include <audio/IAudioSource.hpp>

namespace CubA4::audio
{
	class IAudioPool;
	class AudioBuffer;

	class AudioSource : 
		public virtual IAudioSource
	{
		using IdType = uint32_t;
	public:
		AudioSource(IdType sourceId, std::shared_ptr<IAudioPool> pool);
		~AudioSource();

		void attachBuffer(std::shared_ptr<IAudioBuffer> buffer) override;
		void play() override;
		void stop() override;

		void setPosition(const CubA4::world::GlobalPosition &pos) override;

		IdType getSourceId() const;
	private:
		const IdType sourceId_;
		const std::weak_ptr<IAudioPool> pool_;

		std::shared_ptr<AudioBuffer> attachedBuffer_;
	};
}