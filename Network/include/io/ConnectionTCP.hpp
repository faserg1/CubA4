#ifndef CONNECTIONTCP_HPP
#define CONNECTIONTCP_HPP

#include "Connection.hpp"
#include <boost/asio/ip/tcp.hpp>
#include <thread>
#include <memory>
#include <atomic>

namespace CubA4
{
	namespace network
	{
		namespace io
		{
			class ConnectionTCP :
				public Connection
			{
			public:
				explicit ConnectionTCP(std::shared_ptr<boost::asio::io_service> service, std::shared_ptr<boost::asio::ip::tcp::socket> socket);
				~ConnectionTCP();

				ConnectionProtocol protocol();
				void send(std::string data);
			protected:
			private:
				std::shared_ptr<boost::asio::io_service> service_;
				std::shared_ptr<boost::asio::ip::tcp::socket> socket_;
				std::thread runThread_;
				std::atomic_bool run_;
				void readLoop();
				void readOne();
			};
		}
	}
}

#endif // CONNECTIONTCP_HPP
