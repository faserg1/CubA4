#include "../../include/io/Factory.hpp"
#include "../../include/io/ConnectionTCP.hpp"
#include "../../include/io/ConnectionUDP.hpp"
#include "../../include/io/ListenerTCP.hpp"

#include <stdexcept>

using namespace CubA4::network::io;

namespace CubA4
{
	namespace network
	{
		namespace io
		{
			struct FactoryData
			{
				
			};
		}
	}
}

namespace
{
	std::shared_ptr<Factory> instance_;
}

Factory::Factory() :
	data_(std::make_shared<FactoryData>())
{
	
}

Factory::~Factory()
{
	
}

std::shared_ptr<Factory> Factory::instance()
{
	if (!instance_)
	{
		instance_ = std::shared_ptr<Factory>(new Factory(), [](Factory *ptr) {delete ptr;});
	}
	return instance_;
}

Factory::fsConnection Factory::connect(ConnectionProtocol protocol, std::string host, std::string serviceName)
{
	return std::async(std::launch::async, [](ConnectionProtocol protocol, std::string host, std::string serviceName) -> std::shared_ptr<Connection>
	{
		auto service = std::make_shared<boost::asio::io_service>();
		switch (protocol)
		{
		case CubA4::network::io::ConnectionProtocol::TCP:
		{
			boost::asio::ip::tcp::resolver resolver(*service);
			boost::asio::ip::tcp::resolver::query query(host, serviceName);
			boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query);
			boost::asio::ip::tcp::endpoint ep = *iter;
			auto socket = std::make_shared<boost::asio::ip::tcp::socket>(*service);
			socket->connect(ep);
			return std::make_shared<ConnectionTCP>(service, socket);
		}
		/*case CubA4::network::io::ConnectionProtocol::UDP:
			break;*/
		default:
			throw std::runtime_error("Invalid protocol");
		}
	}, protocol, host, serviceName).share();
}

Factory::fsListener Factory::listen(ConnectionProtocol protocol, unsigned short port)
{
	return std::async(std::launch::async, [](ConnectionProtocol protocol, unsigned short port) -> std::shared_ptr<Listener>
	{
		auto service = std::make_shared<boost::asio::io_service>();
		
		switch (protocol)
		{
		case CubA4::network::io::ConnectionProtocol::TCP:
		{
			boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port);
			auto acc = std::make_shared<boost::asio::ip::tcp::acceptor>(*service, ep);
			acc->open(ep.protocol());
			acc->bind(ep);
			return std::make_shared<ListenerTCP>(service, acc);
		}
		/*case CubA4::network::io::ConnectionProtocol::UDP:
			break;*/
		default:
			break;
		}
		return std::shared_ptr<Listener>();
	}, protocol, port).share();
}