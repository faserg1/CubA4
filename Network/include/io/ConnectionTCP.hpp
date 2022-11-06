#pragma once

#include "Connection.hpp"
#include <boost/asio/ip/tcp.hpp>
#include <thread>
#include <memory>
#include <atomic>
#include <logging/ILogger.hpp>

namespace CubA4::network::io
{
	class ConnectionTCP :
		public Connection
	{
	public:
		explicit ConnectionTCP(std::shared_ptr<boost::asio::io_context> service,
			std::shared_ptr<boost::asio::ip::tcp::socket> socket,
			std::shared_ptr<CubA4::logging::ILogger> logger);
		~ConnectionTCP();

		ConnectionProtocol protocol() override;
		std::shared_future<void> send(const std::string &data) override;
	protected:
	private:
		std::shared_ptr<boost::asio::io_context> service_;
		std::shared_ptr<boost::asio::ip::tcp::socket> socket_;
		std::shared_ptr<CubA4::logging::ILogger> logger_;
		std::thread runThread_;
		std::atomic_bool run_;
		void readLoop();
		void readOne();
	};
}
