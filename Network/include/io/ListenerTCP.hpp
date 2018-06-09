#ifndef LISTENERTCP_HPP
#define LISTENERTCP_HPP

#include "Listener.hpp"
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
			class ListenerTCP :
				public Listener
			{
			public:
				explicit ListenerTCP(std::shared_ptr<boost::asio::io_service> service, std::shared_ptr<boost::asio::ip::tcp::acceptor> accepter);
				~ListenerTCP();
			protected:
			private:
				std::shared_ptr<boost::asio::io_service> service_;
				std::shared_ptr<boost::asio::ip::tcp::acceptor> accepter_;
			};
		}
	}
}

#endif // LISTENERTCP_HPP
