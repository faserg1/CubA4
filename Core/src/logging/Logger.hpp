#pragma once

#include <logging/ILogger.hpp>
#include <string>
#include <memory>

namespace CubA4::logging
{
	class Logger :
		public virtual ILogger
	{
	public:
		static std::shared_ptr <ILogger> create(std::string logsPath);
		~Logger();

		void log(LogSourceSystem system, const std::string &tag,
			LogLevel level, const std::string &message) override;

		void log(LogSourceSystem system, const std::string &tag,
			LogLevel level, const std::string &message, const char *filename, int line) override;

		void flush() override;

		std::shared_ptr<ILoggerTagged> createTaggedLog(LogSourceSystem system, const std::string &tag) override;
	protected:
		explicit Logger(std::string logsPath);
		Logger(const Logger &) = delete;

		virtual std::string getTagString(LogSourceSystem system);
		virtual std::string getLevelString(LogLevel level);
		virtual std::string getTimeString(const char *format);
	private:
		std::string getNextLogName();
		std::string getLogFullName(const std::string &fileName);
		const std::string logsPath_;
		std::weak_ptr<ILogger> this_;
	};
}
