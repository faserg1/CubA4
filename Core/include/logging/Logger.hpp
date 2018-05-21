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
				static std::shared_ptr <ILogger> create(std::string logsPath);
				~Logger();

				void log(LogSourceSystem system, const std::string &tag,
					LogLevel level, const std::string &message) override;

				ILoggerTagged *createTaggedLog(LogSourceSystem system, const std::string &tag) override;
			protected:
				explicit Logger(std::string logsPath);

				virtual std::string getTagString(LogSourceSystem system);
				virtual std::string getLevelString(LogLevel level);
				virtual std::string getTimeString(const char *format);
			private:
				std::string getNextLogName();
				void openLogStream();
				std::shared_ptr<LoggerStreams> stream_;
				const std::string logsPath_;
				std::weak_ptr<ILogger> this_;
			};
		}
	}
}

#endif // LOGGER_HPP
