#include "../../include/io/ConnectionTCP.hpp"
#include <boost/asio/streambuf.hpp>
#include <boost/asio/read.hpp>
using namespace CubA4::network::io;

ConnectionTCP::ConnectionTCP(std::shared_ptr<boost::asio::io_service> service, std::shared_ptr<boost::asio::ip::tcp::socket> socket) :
	service_(service), socket_(socket)
{
	run_ = true;
	runThread_ = std::thread(&ConnectionTCP::readLoop, this);
}

ConnectionTCP::~ConnectionTCP()
{
	run_ = false;
	socket_->close();
	runThread_.join();
}

ConnectionProtocol ConnectionTCP::protocol()
{
	return ConnectionProtocol::TCP;
}

void ConnectionTCP::send(std::string data)
{
	//TODO: [OOKAMI] реализовать
	socket_->async_write_some(boost::asio::buffer(data.data(), data.size()), [](const boost::system::error_code& error, size_t bytesTransferred)
	{

	});
}

void ConnectionTCP::readLoop()
{
	while (run_)
	{
		readOne();
		service_->run_one();
		std::this_thread::yield();
	}
}

void ConnectionTCP::readOne()
{
	if (!socket_->available())
		return;
	std::shared_ptr<boost::asio::streambuf> readBuffer = std::make_shared<boost::asio::streambuf>();
	auto handler = [this, readBuffer](const boost::system::error_code& error, size_t bytesTransferred)
	{
		if (!error)
			this->readed(std::make_shared<std::string>(boost::asio::buffer_cast<const char *>(readBuffer->data()), bytesTransferred));
		else
		{
			// TODO: [OOKAMI] Handle error
		}
	};
	boost::asio::async_read(*socket_, *readBuffer, boost::asio::transfer_all(), handler);
}