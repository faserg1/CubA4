#include "../../include/system/Startup.hpp"
using namespace CubA4::core::system;
using namespace CubA4::core;

Startup::Startup(std::weak_ptr<const ICore> core) :
	core_(core)
{
	
}

Startup::~Startup()
{
	
}

