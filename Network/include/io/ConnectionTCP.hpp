#ifndef NETWORK_CONNECTIONTCP_HPP
#define NETWORK_CONNECTIONTCP_HPP

#include "Connection.hpp"
#include <boost/asio/ip/tcp.hpp>
#include <thread>
#include <memory>
#include <atomic>

namespace CubA4
{
	namespace core
	{
		namespace logging
		{
			class ILogger;
		}
	}

	namespace network
	{
		namespace io
		{
			class ConnectionTCP :
				public Connection
			{
			public:
				explicit ConnectionTCP(std::shared_ptr<boost::asio::io_context> service,
					std::shared_ptr<boost::asio::ip::tcp::socket> socket,
					std::shared_ptr<CubA4::core::logging::ILogger> logger);
				~ConnectionTCP();

				ConnectionProtocol protocol() override;
				std::shared_future<void> send(const std::string &data) override;
			protected:
			private:
				std::shared_ptr<boost::asio::io_context> service_;
				std::shared_ptr<boost::asio::ip::tcp::socket> socket_;
				std::shared_ptr<CubA4::core::logging::ILogger> logger_;
				std::thread runThread_;
				std::atomic_bool run_;
				void readLoop();
				void readOne();
			};
		}
	}
}

#endif // NETWORK_CONNECTIONTCP_HPP
