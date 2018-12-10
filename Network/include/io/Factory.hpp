#ifndef NETWORK_FACTORY_HPP
#define NETWORK_FACTORY_HPP

#include <memory>
#include <string>
#include <future>
#include "../NetworkLibrary.hpp"
#include "Connection.hpp"
#include "Listener.hpp"

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
			class LIBRARY_SHARED Factory
			{
			public:
				explicit Factory(std::shared_ptr<CubA4::core::logging::ILogger> logger);
				~Factory();

				using fsConnection = std::shared_future<std::shared_ptr<Connection>>;
				using fsListener = std::shared_future<std::shared_ptr<Listener>>;

				fsConnection connect(ConnectionProtocol protocol, std::string host, unsigned short port);
				fsConnection connect(ConnectionProtocol protocol, std::string host, std::string serviceName);
				fsListener listen(ConnectionProtocol protocol, unsigned short port);
			protected:
				
			private:
				std::shared_ptr<CubA4::core::logging::ILogger> logger_;
			};
		}
	}
}

#endif // NETWORK_FACTORY_HPP
