#include "../include/io/Connection.hpp"
#include <algorithm>
#include <future>
using namespace CubA4::network::io;

Connection::Connection()
{
	
}

Connection::~Connection()
{
	
}

void Connection::subscribe(cReadFunc readFunc)
{
	subscribers_.push_back(readFunc);
}

void Connection::readed(std::shared_ptr<const std::string> data)
{
	std::for_each(subscribers_.begin(), subscribers_.end(), [data](Connection::cReadFunc func)
	{
		std::async(std::launch::async, func, data);
	});
}