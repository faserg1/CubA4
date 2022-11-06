#pragma once

#include <string>
#include <memory>
#include <logging/LogCommon.hpp>
#include <logging/ILoggerTagged.hpp>

namespace CubA4::logging
{
	class ILogger
	{
	public:
		virtual void log(LogSourceSystem system, const std::string &tag,
			LogLevel level, const std::string &message) = 0;
		virtual void log(LogSourceSystem system, const std::string &tag,
			LogLevel level, const std::string &message, const char *filename, int line) = 0;
		virtual void flush() = 0;

		virtual std::shared_ptr<ILoggerTagged> createTaggedLog(LogSourceSystem system, const std::string &tag) = 0;
	protected:
		virtual ~ILogger() = default;
		explicit ILogger() = default;
	};
}
