#include "../../include/io/ConnectionUDP.hpp"
using namespace CubA4::network::io;

ConnectionUDP::ConnectionUDP(std::shared_ptr<boost::asio::io_context> service,
	std::shared_ptr<boost::asio::ip::udp::socket> socket,
	boost::asio::ip::udp::endpoint endpoint,
	std::shared_ptr<CubA4::logging::ILogger> logger) :
	service_(service), socket_(socket), endpoint_(endpoint), logger_(logger)
{
	
}

ConnectionUDP::~ConnectionUDP()
{
	
}

ConnectionProtocol ConnectionUDP::protocol()
{
	return ConnectionProtocol::UDP;
}

std::shared_future<void> ConnectionUDP::send(const std::string &data)
{
	return std::shared_future<void>();
}