#include "ModVanillaInfo.hpp"]
#include "../include/core/info/Version.hpp"
#include "../include/core/info/VersionDependency.hpp"
#include <stdexcept>
using namespace CubA4::core::info;
using namespace CubA4::mod;

static const auto modVersion = Version(0, 0, 1);
static const auto appDep = VersionDependency(Version(0, 0), Version(0, 0, 1));

std::wstring ModVanillaInfo::getName() const
{
	return L"Vanilla";
}

std::string ModVanillaInfo::getIdName() const
{
	return "vanilla";
}

const IVersion &ModVanillaInfo::getVersion() const
{
	return modVersion;
}

const IVersionDependency &ModVanillaInfo::getAppDependency() const
{
	return appDep;
}

std::vector<std::string> ModVanillaInfo::getRequiredMods() const
{
	return {};
}

std::vector<std::string> ModVanillaInfo::getPreferedMods() const
{
	return {};
}

const IVersionDependency &ModVanillaInfo::getModDependency(std::string modIdName) const
{
	//TODO: [OOKAMI] Заменить выбрасываемое исключение
	throw std::runtime_error("Мод " + modIdName + " не нужен для загрузки.");
}