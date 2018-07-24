#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include <string>
#include "LogCommon.hpp"

namespace CubA4
{
	namespace core
	{
		namespace logging
		{
			class ILogger
			{
			public:
				virtual void log(LogSourceSystem system, const std::string &tag,
					LogLevel level, const std::string &message) = 0;
				virtual void flush() = 0;

				virtual ILoggerTagged *createTaggedLog(LogSourceSystem system, const std::string &tag) = 0;
			protected:
				virtual ~ILogger() {}
				explicit ILogger() {}
			};
		}
	}
}

#endif // ILOGGER_HPP