#include "../../include/io/ConnectionUDP.hpp"
using namespace CubA4::network::io;

ConnectionUDP::ConnectionUDP()
{
	
}

ConnectionUDP::~ConnectionUDP()
{
	
}

ConnectionProtocol ConnectionUDP::protocol()
{
	return ConnectionProtocol::UDP;
}