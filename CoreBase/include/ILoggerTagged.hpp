#ifndef ILOGGERTAGGED_HPP
#define ILOGGERTAGGED_HPP

#include <string>
#include "LogCommon.hpp"

namespace CubA4
{
	namespace core
	{
		class ILoggerTagged
		{
		public:
			virtual ~ILoggerTagged() {}
			
			void log(LogLevel level, const std::string &message) = 0;
		protected:
			explicit ILoggerTagged() {}
		};
	}
}

#endif // ILOGGERTAGGED_HPP