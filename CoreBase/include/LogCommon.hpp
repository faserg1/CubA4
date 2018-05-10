#ifndef LOGCOMMON_HPP
#define LOGCOMMON_HPP

namespace CubA4
{
	namespace core
	{
		enum class LogSourceSystem
		{
			Core,
			Network,
			Render,
			Mod,
			App,
		};
		
		enum class LogLevel
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

#endif // LOGCOMMON_HPP