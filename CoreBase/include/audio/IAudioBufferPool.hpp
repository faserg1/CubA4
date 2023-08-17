#pragma once

#include <memory>

namespace CubA4::audio
{
	class IAudioBuffer;

	class IAudioBufferPool
	{
	public:
		virtual std::shared_ptr<IAudioBuffer> getBuffer() = 0;
	protected:
		IAudioBufferPool() = default;
		virtual ~IAudioBufferPool() = default;
	};
}