#pragma once

#include <audio/IAudioBuffer.hpp>
#include <audio/IAudioPool.hpp>
#include <audio/IAudioBufferPool.hpp>
#include <memory>
#include <vector>
#include <cstdint>

namespace CubA4::audio
{
	class AudioBufferPool :
		public std::enable_shared_from_this<AudioBufferPool>,
		virtual public IAudioPool,
		virtual public IAudioBufferPool
	{
	public:
		AudioBufferPool();
		~AudioBufferPool();

		std::shared_ptr<IAudioBuffer> getBuffer() override;
	protected:
		void free(IdType id) override;
	private:
		void allocateBuffers();
		void deallocateBuffers();
	private:
		static const uint64_t allocationCount_ = 64;
		std::vector<uint32_t> bufferIds_;
	};
}