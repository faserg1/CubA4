#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <logging/ILogger.hpp>
#include <string>
#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace config
		{
			class IFilePaths;
		}

		namespace logging
		{
			class LoggerStreams;

			class Logger :
				public virtual ILogger
			{
			public:
				explicit Logger();
				~Logger();
			protected:
			private:
				std::string getNextLogName();
				void openLogStream();
				std::unique_ptr<LoggerStreams> stream_;
				std::shared_ptr<const config::IFilePaths> paths_;
			};
		}
	}
}

#endif // LOGGER_HPP
