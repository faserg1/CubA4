#include <loader/ModLoader.hpp>
#include <vector>
using namespace CubA4::mod_loader;

struct ModLoader::Private
{

};

ModLoader::ModLoader()
{
	data_ = std::make_shared<Private>();
}

ModLoader::~ModLoader()
{
	
}