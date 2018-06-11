#include "../../include/io/Factory.hpp"
#include "../../include/io/ConnectionTCP.hpp"
#include "../../include/io/ConnectionUDP.hpp"
#include "../../include/io/ListenerTCP.hpp"
#include <logging/ILogger.hpp>
#include <stdexcept>

using namespace CubA4::network::io;

Factory::Factory(std::shared_ptr<CubA4::core::logging::ILogger> logger) :
	logger_(logger)
{
	
}

Factory::~Factory()
{
	
}

Factory::fsConnection Factory::connect(ConnectionProtocol protocol, std::string host, unsigned short port)
{
	return connect(protocol, host, std::to_string(port));
}

Factory::fsConnection Factory::connect(ConnectionProtocol protocol, std::string host, std::string serviceName)
{
	return std::async(std::launch::async, [this](ConnectionProtocol protocol, std::string host, std::string serviceName) -> std::shared_ptr<Connection>
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
			try
			{
				socket->connect(ep);
			}
			catch (boost::system::system_error &error)
			{
				std::string msg = "Code: " + std::to_string(error.code().value()) + ", Msg: " + error.what();
				logger_->log(CubA4::core::logging::LogSourceSystem::Network, "FACTORY", CubA4::core::logging::LogLevel::Error, msg);
			}
			return std::make_shared<ConnectionTCP>(service, socket, logger_);
		}
		case CubA4::network::io::ConnectionProtocol::UDP:
		{
			boost::asio::ip::udp::resolver resolver(*service);
			boost::asio::ip::udp::resolver::query query(host, serviceName);
			boost::asio::ip::udp::resolver::iterator iter = resolver.resolve(query);
			boost::asio::ip::udp::endpoint ep = *iter;
			auto socket = std::make_shared<boost::asio::ip::udp::socket>(*service);
			try
			{
				socket->open(ep.protocol());
			}
			catch (boost::system::system_error &error)
			{
				std::string msg = "Code: " + std::to_string(error.code().value()) + ", Msg: " + error.what();
				logger_->log(CubA4::core::logging::LogSourceSystem::Network, "FACTORY", CubA4::core::logging::LogLevel::Error, msg);
			}
			return std::make_shared<ConnectionUDP>(service, socket, ep, logger_);
		}
		default:
			throw std::runtime_error("Invalid protocol");
		}
	}, protocol, host, serviceName).share();
}

Factory::fsListener Factory::listen(ConnectionProtocol protocol, unsigned short port)
{
	return std::async(std::launch::async, [this](ConnectionProtocol protocol, unsigned short port) -> std::shared_ptr<Listener>
	{
		auto service = std::make_shared<boost::asio::io_service>();
		
		switch (protocol)
		{
		case CubA4::network::io::ConnectionProtocol::TCP:
		{
			boost::asio::ip::tcp::endpoint ep(boost::asio::ip::tcp::v4(), port);
			auto acc = std::make_shared<boost::asio::ip::tcp::acceptor>(*service, ep);
			try
			{
				acc->listen();
				//acc->bind(ep);
			}
			catch (boost::system::system_error &error)
			{
				std::string msg = "Code: " + std::to_string(error.code().value()) + ", Msg: " + error.what();
				logger_->log(CubA4::core::logging::LogSourceSystem::Network, "FACTORY", CubA4::core::logging::LogLevel::Error, msg);
			}
			return std::make_shared<ListenerTCP>(service, acc, logger_);
		}
		/*case CubA4::network::io::ConnectionProtocol::UDP:
			break;*/
		default:
			break;
		}
		return std::shared_ptr<Listener>();
	}, protocol, port).share();
}