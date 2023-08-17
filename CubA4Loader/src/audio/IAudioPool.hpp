#pragma once

#include <cstdint>

namespace CubA4::audio
{
	class IAudioPool
	{
	protected:
		using IdType = uint32_t;
	public:
		virtual void free(IdType id) = 0;
	protected:
		IAudioPool() = default;
		virtual ~IAudioPool() = default;
	};
}