#include "loader/ModLoader.hpp"
#include <ICore.hpp>
#include <vector>
using namespace CubA4::mod_loader;
using namespace CubA4::core;
using namespace CubA4::core::config;

ModLoader::ModLoader(std::shared_ptr<const ICore> core) :
	core_(core)
{
	
}

ModLoader::~ModLoader()
{
	
}