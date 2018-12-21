#ifndef CORE_LOGGERSTREAMS_HPP
#define CORE_LOGGERSTREAMS_HPP

#include <ostream>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/device/file.hpp>
#include <functional>
#include <atomic>
#include <mutex>

namespace CubA4
{
	namespace core
	{
		namespace logging
		{
			class LoggerStreams
			{
			public:
				LoggerStreams(std::function<std::string()> getNewName);
				~LoggerStreams();
				void flush();
				void write(const std::string &line);
			private:
				std::function<std::string()> getNewName_;
				boost::iostreams::stream_buffer<boost::iostreams::file_sink> buf_;
				std::ostream out_;
			private:
			};
		}
	}
}

#endif // CORE_LOGGERSTREAMS_HPP
