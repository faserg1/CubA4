#ifndef COREBASE_ILOGGERTAGGED_HPP
#define COREBASE_ILOGGERTAGGED_HPP

#include <string>
#include "LogCommon.hpp"

namespace CubA4
{
	namespace core
	{
		namespace logging
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
	}
}

#endif // COREBASE_ILOGGERTAGGED_HPP