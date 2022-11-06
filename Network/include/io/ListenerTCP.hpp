#pragma once

#include "Listener.hpp"
#include <boost/asio/ip/tcp.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <logging/ILogger.hpp>

namespace CubA4::network::io
{
	class Connection;

	class ListenerTCP :
		public Listener
	{
	public:
		explicit ListenerTCP(std::shared_ptr<boost::asio::io_context> service,
			std::shared_ptr<boost::asio::ip::tcp::acceptor> accepter,
			std::shared_ptr<CubA4::logging::ILogger> logger);
		~ListenerTCP();
		void subscribe(std::function<void(std::shared_ptr<Connection>)> subscriber) override;
	protected:
	private:
		std::shared_ptr<boost::asio::io_context> service_;
		std::shared_ptr<boost::asio::ip::tcp::acceptor> accepter_;
		std::shared_ptr<CubA4::logging::ILogger> logger_;
		std::thread runThread_;
		std::atomic_bool run_;
		std::vector<std::function<void(std::shared_ptr<Connection>)>> subscribers_;
		void acceptLoop();
	};
}
