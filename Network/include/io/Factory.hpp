#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <memory>
#include <string>
#include <future>
#include "../NetworkLibrary.hpp"
#include "Connection.hpp"
#include "Listener.hpp"

namespace CubA4
{
	namespace network
	{
		namespace io
		{
			struct FactoryData;

			class LIBRARY_SHARED Factory
			{
			public:
				static std::shared_ptr<Factory> instance();
				using fsConnection = std::shared_future<std::shared_ptr<Connection>>;
				using fsListener = std::shared_future<std::shared_ptr<Listener>>;

				fsConnection connect(ConnectionProtocol protocol, std::string host, std::string serviceName);
				fsListener listen(ConnectionProtocol protocol, unsigned short port);
			protected:
				explicit Factory();
				~Factory();
			private:
				std::shared_ptr<FactoryData> data_;
			};
		}
	}
}

#endif // FACTORY_HPP
