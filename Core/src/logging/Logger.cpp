#include "Logger.hpp"
#include <logging/ILoggerTagged.hpp>
#include <filesystem>
#include <loguru/loguru.hpp>


#include <stdexcept>
#include <chrono>
#include <iomanip>
#include <cstdio>
#include <cmath>
using namespace CubA4::logging;

namespace CubA4::logging
{
	namespace
	{
		class LoggerTagged :
			public virtual ILoggerTagged
		{
		public:
			LoggerTagged(std::shared_ptr<ILogger> logger, LogSourceSystem system, const std::string &tag) :
				logger_(logger), system_(system), tag_(tag)
			{

			}
			void log(LogLevel level, const std::string &message) override
			{
				logger_->log(system_, tag_, level, message);
			}
			void flush() override
			{
				logger_->flush();
			}
		private:
			const std::shared_ptr<ILogger> logger_;
			const LogSourceSystem system_;
			const std::string tag_;
		};

		constexpr loguru::Verbosity toLoguruVerbosity(LogLevel level)
		{
			switch (level)
			{
				case LogLevel::Warning:
					return loguru::Verbosity_WARNING;
				case LogLevel::Error:
					return loguru::Verbosity_ERROR;
				case LogLevel::Critical:
					return loguru::Verbosity_FATAL;
			}
			return loguru::Verbosity_INFO;
		}
	}
}

Logger::Logger(std::string logsPath) :
	logsPath_(logsPath)
{
	const auto logName = getNextLogName();
	const auto logNameLatest = getLogFullName("latest.log");
	loguru::add_file(logName.c_str(), loguru::FileMode::Truncate, loguru::Verbosity_MAX);
	loguru::add_file(logNameLatest.c_str(), loguru::FileMode::Truncate, loguru::Verbosity_MAX);
}

std::shared_ptr<ILogger> Logger::create(std::string logsPath)
{
	//Make shared не сработает в приватной/защищенной области видимости
	auto ptr = std::shared_ptr<Logger>(new Logger(logsPath));
	ptr->this_ = ptr;
	return ptr;
}

Logger::~Logger()
{
	flush();
}

void Logger::log(LogSourceSystem system, const std::string &tag, LogLevel level, const std::string &message, const char *filename, int line)
{
	loguru::log(toLoguruVerbosity(level), filename, line, "[{}:{}] {}", getTagString(system), tag, message);
	if (level == LogLevel::Error || level == LogLevel::Critical)
		flush();
}

void Logger::log(LogSourceSystem system, const std::string &tag, LogLevel level, const std::string &message)
{
	log(system, tag, level, message, "unknow file", -1);
}


void Logger::flush()
{
	loguru::flush();
}

std::shared_ptr<ILoggerTagged> Logger::createTaggedLog(LogSourceSystem system, const std::string &tag)
{
	if (auto ptr = this_.lock())
		return  std::make_shared<LoggerTagged>(ptr, system, tag);
	return {};
}

std::string Logger::getTagString(LogSourceSystem system)
{
	switch (system)
	{
	case CubA4::logging::LogSourceSystem::Core:
		return "CORE";
	case CubA4::logging::LogSourceSystem::Network:
		return "NETWOWK";
	case CubA4::logging::LogSourceSystem::Render:
		return "RENDER";
	case CubA4::logging::LogSourceSystem::Mod:
		return "MOD";
	case CubA4::logging::LogSourceSystem::App:
		return "APP";
	}
	throw std::runtime_error("Unknown log tag:" + std::to_string(static_cast<int>(system)));
}

std::string CubA4::logging::Logger::getLevelString(LogLevel level)
{
	switch (level)
	{
	case CubA4::logging::LogLevel::Debug:
		return "DBG";
	case CubA4::logging::LogLevel::Info:
		return "INF";
	case CubA4::logging::LogLevel::Warning:
		return "WRN";
	case CubA4::logging::LogLevel::Error:
		return "ERR";
	case CubA4::logging::LogLevel::Critical:
		return "CRT";
	}
	throw std::runtime_error("Unknown log level:" + std::to_string(static_cast<int>(level)));
}

std::string CubA4::logging::Logger::getTimeString(const char *format)
{
	auto nowSystem = std::chrono::system_clock::now();
	std::time_t time = std::chrono::system_clock::to_time_t(nowSystem);
	auto *localTime = std::localtime(&time);
	constexpr unsigned bufferSize = 50;
	char buffer[bufferSize];
	const size_t len = std::strftime(buffer, bufferSize, format, localTime);
	if (!len)
		throw std::runtime_error("Cannot format time!");
	std::string result(buffer, len);
	auto posFind = result.find("%k");
	if (posFind != result.npos)
	{
		const auto formatMs = "%." + std::to_string((unsigned) ::log10(CLOCKS_PER_SEC) + 1) + "u";
		snprintf(buffer, bufferSize, formatMs.data(), nowSystem.time_since_epoch().count() % CLOCKS_PER_SEC);
		result = result.replace(posFind, 2, buffer);
	}
	return result;
}

std::string Logger::getNextLogName()
{
	return getLogFullName(getTimeString("log%F_%H.%M.%S.txt"));
}

std::string Logger::getLogFullName(const std::string &fileName)
{
	std::filesystem::path path(logsPath_);
	if (!std::filesystem::exists(path))
		std::filesystem::create_directories(path);
	return (path / fileName).string();
}