#include <app/ServerVersion.hpp>
using namespace CubA4::app;

unsigned short ServerVersion::major() const
{
	return 0;
}

unsigned short ServerVersion::minor() const
{
	return 1;
}

unsigned short ServerVersion::patch() const
{
	return 0;
}

// TODO: [OOKAMI] При авто-билдах заполнять эти значения через макросы

int ServerVersion::build() const
{
	return -1;
}

int ServerVersion::revision() const
{
	return -1;
}

std::string ServerVersion::to_string() const
{
	// TODO: [OOKAMI] Более круто выводить версию
	return std::to_string(major()) + "." + std::to_string(minor()) + "." + std::to_string(patch());
}