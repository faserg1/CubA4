#include "../../include/io/ConnectionTCP.hpp"
#include <boost/asio/streambuf.hpp>
#include <boost/asio/read.hpp>
#include <logging/ILogger.hpp>
using namespace CubA4::network::io;

ConnectionTCP::ConnectionTCP(std::shared_ptr<boost::asio::io_context> service,
	std::shared_ptr<boost::asio::ip::tcp::socket> socket,
	std::shared_ptr<CubA4::core::logging::ILogger> logger) :
	service_(service), socket_(socket), logger_(logger)
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

std::shared_future<void> ConnectionTCP::send(const std::string &data)
{
	auto dataCopy = std::make_shared<std::string>(data);
	auto promise = std::make_shared<std::promise<void>>();
	//TODO: [OOKAMI] реализовать
	socket_->async_write_some(boost::asio::buffer(dataCopy->data(), dataCopy->size()), [dataCopy, promise](const boost::system::error_code& error, size_t bytesTransferred)
	{
		if (!error)
			promise->set_value();
		else
		{
			try
			{
				throw boost::system::system_error(error);
			}
			catch (...)
			{
				promise->set_exception(std::current_exception());
			}
		}
	});
	return promise->get_future().share();
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
	auto handler = [this, readBuffer](const boost::system::error_code& errorCode, size_t bytesTransferred)
	{
		if (!errorCode || errorCode == boost::asio::error::eof)
			this->readed(std::make_shared<std::string>(boost::asio::buffer_cast<const char *>(readBuffer->data()), bytesTransferred));
		else
		{
			boost::system::system_error error(errorCode);
			std::string msg = "Code: " + std::to_string(error.code().value()) + ", Msg: " + error.what();
			logger_->log(CubA4::core::logging::LogSourceSystem::Network, "CONNECTIONTCP", CubA4::core::logging::LogLevel::Error, msg);
		}
	};
	boost::asio::async_read(*socket_, *readBuffer, boost::asio::transfer_all(), handler);
}