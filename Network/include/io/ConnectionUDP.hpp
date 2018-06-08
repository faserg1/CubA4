#ifndef CONNECTIONUDP_HPP
#define CONNECTIONUDP_HPP

#include "Connection.hpp"
#include <boost/asio/ip/udp.hpp>

namespace CubA4
{
	namespace network
	{
		namespace io
		{
			class ConnectionUDP :
				public Connection
			{
			public:
				explicit ConnectionUDP();
				~ConnectionUDP();

				ConnectionProtocol protocol();
			protected:
			private:
			};
		}
	}
}

#endif // CONNECTIONUDP_HPP
