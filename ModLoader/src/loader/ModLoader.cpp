#include <loader/ModLoader.hpp>
#include <vector>
using namespace CubA4::mod_loader;

struct ModLoader::Private
{

};

ModLoader::ModLoader()
{
	data_ = new Private();
}

ModLoader::~ModLoader()
{
	delete data_;
}