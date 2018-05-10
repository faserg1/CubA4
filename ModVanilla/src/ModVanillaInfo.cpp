#include "ModVanillaInfo.hpp"

std::wstring CubA4::mod::ModVanillaInfo::getName()
{
	return L"Vanilla";
}

std::string CubA4::mod::ModVanillaInfo::getIdName()
{
	return "vanilla";
}

void CubA4::mod::ModVanillaInfo::getVersion(int16_t & major, int16_t & minor, int16_t & patch)
{
	major = 0;
	minor = 1;
	patch = 0;
}
