#ifndef NETWORK_LISTENER_HPP
#define NETWORK_LISTENER_HPP

#include <functional>
#include <memory>

namespace CubA4
{
	namespace network
	{
		namespace io
		{
			class Connection;

			class Listener
			{
			public:
				explicit Listener();
				virtual ~Listener();
				virtual void subscribe(std::function<void(std::shared_ptr<Connection>)> subscriber) = 0;
			protected:
			private:
			};
		}
	}
}

#endif // NETWORK_LISTENER_HPP
