#include "./LoggerStreams.hpp"
using namespace CubA4::core::logging;

constexpr const uint64_t linesMaximum = 100000;

LoggerStreams::LoggerStreams(std::function<std::string()> getNewName):
	getNewName_(getNewName), buf_(getNewName()), out_(&buf_)
{
	
}

LoggerStreams::~LoggerStreams()
{
	
}

void LoggerStreams::flush()
{
	out_.flush();
}

void LoggerStreams::write(const std::string &line)
{
	out_.write(line.c_str(), line.size());
}