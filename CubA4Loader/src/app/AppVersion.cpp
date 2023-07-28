#include "./AppVersion.hpp"
using namespace CubA4::app;

unsigned short AppVersion::major() const
{
	return 0;
}

unsigned short AppVersion::minor() const
{
	return 1;
}

unsigned short AppVersion::patch() const
{
	return 0;
}

// TODO: [OOKAMI] При авто-билдах заполнять эти значения через макросы

int AppVersion::build() const
{
	return -1;
}

int AppVersion::revision() const
{
	return -1;
}

std::string AppVersion::to_string() const
{
	// TODO: [OOKAMI] Более круто выводить версию
	return std::to_string(major()) + "." + std::to_string(minor()) + "." + std::to_string(patch());
}