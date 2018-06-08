#include "../../include/io/ConnectionTCP.hpp"
#include <boost/asio/streambuf.hpp>
#include <boost/asio/read.hpp>
using namespace CubA4::network::io;

ConnectionTCP::ConnectionTCP(std::shared_ptr<boost::asio::ip::tcp::socket> socket) :
	socket_(socket)
{
	read_ = true;
	runThread_ = std::thread(&ConnectionTCP::readLoop, this);
}

ConnectionTCP::~ConnectionTCP()
{
	read_ = false;
	runThread_.join();
}

ConnectionProtocol ConnectionTCP::protocol()
{
	return ConnectionProtocol::TCP;
}

void ConnectionTCP::readLoop()
{
	while (read_)
	{
		boost::asio::streambuf read_buffer;
		auto readed = boost::asio::read(*socket_, read_buffer, boost::asio::transfer_all());
	}
}