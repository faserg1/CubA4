#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <logging/ILogger.hpp>

namespace CubA4
{
	namespace core
	{
		namespace logging
		{
			class Logger :
				public virtual ILogger
			{
			public:
				explicit Logger();
				~Logger();
			protected:
			private:
			};
		}
	}
}

#endif // LOGGER_HPP
