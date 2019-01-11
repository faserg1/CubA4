#include "./Resource.hpp"
using namespace CubA4::core::resources;
using namespace CubA4::core::filesystem;

Resource::Resource(boost::filesystem::path) :
	File(path)
{
	
}

Resource::~Resource()
{
	
}

