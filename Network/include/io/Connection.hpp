#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "NetworkLibrary.hpp"
#include <functional>
#include <vector>
#include <memory>

namespace CubA4
{
	namespace network
	{
		namespace io
		{
			enum class ConnectionProtocol
			{
				TCP,
				UDP
			};

			class LIBRARY_SHARED Connection
			{
			public:
				using cReadFunc = std::function<void(std::shared_ptr<const std::string>)>;
				virtual ~Connection();

				virtual ConnectionProtocol protocol() = 0;
				virtual void send(std::string data) = 0;
				void subscribe(cReadFunc readFunc);
			protected:
				explicit Connection();
				void readed(std::shared_ptr<const std::string> data);
			private:
				std::vector<cReadFunc> subscribers_;
			};
		}
	}
}

#endif // CONNECTION_HPP
