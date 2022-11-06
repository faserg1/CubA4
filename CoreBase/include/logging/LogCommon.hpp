#pragma once

namespace CubA4::logging
{
	enum class LogSourceSystem : char
	{
		Core,
		Network,
		Render,
		Mod,
		App,
	};

	enum class LogLevel : char
	{
		Debug,
		Info,
		Warning,
		Error,
		Critical
	};
}
