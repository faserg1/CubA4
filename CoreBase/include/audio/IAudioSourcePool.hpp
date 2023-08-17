#pragma once

#include <memory>

namespace CubA4::audio
{
	class IAudioSource;

	class IAudioSourcePool
	{
	public:
		virtual std::unique_ptr<IAudioSource> getSource() = 0;
	protected:
		IAudioSourcePool() = default;
		virtual ~IAudioSourcePool() = default;
	};
}