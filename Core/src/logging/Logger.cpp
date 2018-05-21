#include "../../include/logging/Logger.hpp"
#include <logging/ILoggerTagged.hpp>
#include <boost/filesystem.hpp>
#include <ostream>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/file.hpp>
#include <stdexcept>
#include <chrono>
#include <iomanip>
using namespace CubA4::core::logging;

namespace CubA4
{
	namespace core
	{
		namespace logging
		{
			class LoggerStreams
			{
				friend class CubA4::core::logging::Logger;

				boost::iostreams::stream_buffer<boost::iostreams::file_sink> buf_;
				std::ostream out_;
			public:
				LoggerStreams(std::string filePath) : buf_(filePath), out_(&buf_)
				{

				}
				~LoggerStreams()
				{
					out_.flush();
				}
			};

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
					void log(LogLevel level, const std::string &message)
					{
						logger_->log(system_, tag_, level, message);
					}
				private:
					const std::shared_ptr<ILogger> logger_;
					const LogSourceSystem system_;
					const std::string tag_;
				};
			}
		}
	}
}

Logger::Logger(std::string logsPath) :
	logsPath_(logsPath)
{
	openLogStream();
}

std::shared_ptr<ILogger> Logger::create(std::string logsPath)
{
	auto ptr = std::make_shared<Logger>(Logger(logsPath));
	ptr->this_ = ptr;
	return ptr;
}

Logger::~Logger()
{
	
}

void Logger::log(LogSourceSystem system, const std::string &tag, LogLevel level, const std::string &message)
{	
	std::string logMsg = "[" + getLevelString(level) + ":" + getTagString(system) + ":" + tag + "]{" + getTimeString("%x-%X") + "} " + message + "\n";
	stream_->out_.write(logMsg.c_str(), logMsg.size());
}

ILoggerTagged *Logger::createTaggedLog(LogSourceSystem system, const std::string &tag)
{
	if (auto ptr = this_.lock())
		return new LoggerTagged(ptr, system, tag);
	return nullptr;
}

std::string Logger::getTagString(LogSourceSystem system)
{
	switch (system)
	{
	case CubA4::core::logging::LogSourceSystem::Core:
		return "CORE";
	case CubA4::core::logging::LogSourceSystem::Network:
		return "NETWOWK";
	case CubA4::core::logging::LogSourceSystem::Render:
		return "RENDER";
	case CubA4::core::logging::LogSourceSystem::Mod:
		return "MOD";
	case CubA4::core::logging::LogSourceSystem::App:
		return "APP";
	}
	throw std::runtime_error("Unknown log tag:" + std::to_string(static_cast<int>(system)));
}

std::string CubA4::core::logging::Logger::getLevelString(LogLevel level)
{
	switch (level)
	{
	case CubA4::core::logging::LogLevel::Debug:
		return "DBG";
	case CubA4::core::logging::LogLevel::Info:
		return "INF";
	case CubA4::core::logging::LogLevel::Warning:
		return "WRN";
	case CubA4::core::logging::LogLevel::Error:
		return "ERR";
	case CubA4::core::logging::LogLevel::Critical:
		return "CRT";
	}
	throw std::runtime_error("Unknown log level:" + std::to_string(static_cast<int>(level)));
}

std::string CubA4::core::logging::Logger::getTimeString(const char *format)
{
	std::time_t time = std::time(nullptr);
	auto *localTime = std::localtime(&time);
	constexpr unsigned bufferSize = 50;
	char buffer[bufferSize];
	const int len = std::strftime(buffer, bufferSize, format, localTime);
	if (!len)
		throw std::runtime_error("Cannot format time!");
	return std::string(buffer, len);
}

std::string Logger::getNextLogName()
{
	boost::filesystem::path path(logsPath_);
	if (!boost::filesystem::exists(path))
		boost::filesystem::create_directories(path);
	return (path / getTimeString("log%F_%H.%M.%S.txt")).string();
}

void Logger::openLogStream()
{
	stream_ = std::make_shared<LoggerStreams>(getNextLogName());
}

