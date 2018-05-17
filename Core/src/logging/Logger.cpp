#include "../../include/logging/Logger.hpp"
#include <boost/filesystem.hpp>
#include <ostream>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/file.hpp>
using namespace CubA4::core::logging;

namespace CubA4
{
	namespace core
	{
		namespace logging
		{
			class LoggerStreams
			{
				boost::iostreams::stream_buffer<boost::iostreams::file_sink> buf_;
				std::ostream out_;

				friend class Logger;
				LoggerStreams(std::string filePath) : buf_(filePath), out_(&buf_)
				{

				}
			};
		}
	}
}

Logger::Logger()
{
	
}

Logger::~Logger()
{
	
}

std::string CubA4::core::logging::Logger::getNextLogName()
{
	return std::string();
}

void CubA4::core::logging::Logger::openLogStream()
{
	stream_ = std::make_unique<LoggerStreams>(getNextLogName());
}

