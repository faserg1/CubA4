#include "ModVanillaInfo.hpp"
#include "ModVanilla.hpp"
#include <ModVanillaConst.hpp>
#include <info/Version.hpp>
#include <info/VersionDependency.hpp>
#include <stdexcept>
using namespace CubA4::info;
using namespace CubA4::mod;

static const auto modVersion = Version(0, 0, 1);
static const auto appDep = VersionDependency(Version(0, 0), Version(0, 0, 1));

ModVanillaInfo::ModVanillaInfo()
{
	
}

ModVanillaInfo::~ModVanillaInfo()
{

}

std::wstring ModVanillaInfo::getName() const
{
	return L"Vanilla";
}

std::string ModVanillaInfo::getIdName() const
{
	return ModVanillaId;
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

std::shared_ptr<IMod> ModVanillaInfo::createMod() const
{
	return std::make_shared<ModVanilla>(*this);
}