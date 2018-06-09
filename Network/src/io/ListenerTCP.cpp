#include "../../include/io/ListenerTCP.hpp"
using namespace CubA4::network::io;

ListenerTCP::ListenerTCP(std::shared_ptr<boost::asio::io_service> service, std::shared_ptr<boost::asio::ip::tcp::acceptor> accepter) :
	service_(service), accepter_(accepter)
{
	
}

ListenerTCP::~ListenerTCP()
{
	
}

