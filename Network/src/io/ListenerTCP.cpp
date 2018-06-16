#include "../../include/io/ListenerTCP.hpp"
#include "../../include/io/ConnectionTCP.hpp"
#include <logging/ILogger.hpp>
using namespace CubA4::network::io;

ListenerTCP::ListenerTCP(std::shared_ptr<boost::asio::io_context> service,
	std::shared_ptr<boost::asio::ip::tcp::acceptor> accepter,
	std::shared_ptr<CubA4::core::logging::ILogger> logger) :
	service_(service), accepter_(accepter), logger_(logger)
{
	run_ = true;
	runThread_ = std::thread(&ListenerTCP::acceptLoop, this);
}

ListenerTCP::~ListenerTCP()
{
	run_ = false;
	accepter_->close();
	runThread_.join();
}

void ListenerTCP::subscribe(std::function<void(std::shared_ptr<Connection>)> subscriber)
{
	subscribers_.push_back(subscriber);
}

void ListenerTCP::acceptLoop()
{
	while (run_)
	{
		auto clientService = std::make_shared<boost::asio::io_context>();
		auto socket = std::make_shared<boost::asio::ip::tcp::socket>(*clientService);
		try
		{
			accepter_->accept(*socket);
		}
		catch (boost::system::system_error &error)
		{
			std::string msg = "Code: " + std::to_string(error.code().value()) + ", Msg: " + error.what();
			logger_->log(CubA4::core::logging::LogSourceSystem::Network, "LISTENERTCP", CubA4::core::logging::LogLevel::Error, msg);
			continue;
		}
		auto clientConnection = std::make_shared<ConnectionTCP>(clientService, socket, logger_);
		auto subsCopy = subscribers_;
		std::thread([clientConnection, subsCopy]()
		{
			for (auto subscriber : subsCopy)
			{
				subscriber(clientConnection);
			}
		});
	}
}