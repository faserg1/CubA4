#ifndef CONNECTIONUDP_HPP
#define CONNECTIONUDP_HPP

#include "Connection.hpp"
#include <boost/asio/ip/udp.hpp>

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
			class ConnectionUDP :
				public Connection
			{
			public:
				explicit ConnectionUDP(std::shared_ptr<boost::asio::io_context> service,
					std::shared_ptr<boost::asio::ip::udp::socket> socket,
					boost::asio::ip::udp::endpoint endpoint,
					std::shared_ptr<CubA4::core::logging::ILogger> logger);
				~ConnectionUDP();

				ConnectionProtocol protocol() override;
				std::shared_future<void> send(const std::string &data) override;
			protected:
			private:
				std::shared_ptr<boost::asio::io_context> service_;
				std::shared_ptr<boost::asio::ip::udp::socket> socket_;
				boost::asio::ip::udp::endpoint endpoint_;
				std::shared_ptr<CubA4::core::logging::ILogger> logger_;
			};
		}
	}
}

#endif // CONNECTIONUDP_HPP
