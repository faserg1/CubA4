#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <memory>

namespace CubA4
{
	namespace network
	{
		namespace io
		{
			class Connection;
			class Listener;

			class Factory
			{
			public:
				explicit Factory();
				~Factory();

				std::shared_ptr<Connection> connect();
				std::shared_ptr<Listener> listen();
			protected:
			private:
			};
		}
	}
}

#endif // FACTORY_HPP
