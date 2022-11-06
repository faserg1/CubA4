#pragma once

#include <string>
#include <logging/LogCommon.hpp>

namespace CubA4::logging
{
	class ILoggerTagged
	{
	public:
		virtual ~ILoggerTagged() = default;

		virtual void log(LogLevel level, const std::string &message) = 0;
		virtual void flush() = 0;
	protected:
		explicit ILoggerTagged() = default;
	};
}
