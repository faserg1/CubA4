#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include <string>
#include <memory>
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

				virtual std::shared_ptr<ILoggerTagged> createTaggedLog(LogSourceSystem system, const std::string &tag) = 0;
			protected:
				virtual ~ILogger() = default;
				explicit ILogger() = default;
			};
		}
	}
}

#endif // ILOGGER_HPP