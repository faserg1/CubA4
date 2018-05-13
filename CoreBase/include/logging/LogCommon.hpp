#ifndef LOGCOMMON_HPP
#define LOGCOMMON_HPP

namespace CubA4
{
	namespace core
	{
		namespace logging
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

			class ILoggerTagged;
			class ILogger;
		}
	}
}

#endif // LOGCOMMON_HPP