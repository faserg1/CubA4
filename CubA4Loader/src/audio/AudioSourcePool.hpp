#pragma once

#include <audio/IAudioBuffer.hpp>
#include <audio/IAudioPool.hpp>
#include <audio/IAudioSourcePool.hpp>
#include <memory>
#include <vector>
#include <cstdint>

namespace CubA4::audio
{
	class AudioSourcePool :
		public std::enable_shared_from_this<AudioSourcePool>,
		virtual public IAudioPool,
		virtual public IAudioSourcePool
	{
	public:
		AudioSourcePool();
		~AudioSourcePool();

		std::unique_ptr<IAudioSource> getSource() override;
	protected:
		void free(IdType id) override;
	private:
		void allocateSources();
		void deallocateSources();
	private:
		static const uint64_t allocationCount_ = 64;
		std::vector<uint32_t> sourceIds_;
	};
}