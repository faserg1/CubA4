#include <mod/ModLinker.hpp>
#include <mod/IMod.hpp>
#include <IModInfo.hpp>
using namespace CubA4::mod;

ModLinker::ModLinker(std::vector<std::shared_ptr<IMod>> mods)
{
	for (auto mod : mods)
	{
		auto name = mod->getInfo().getIdName();
		mods_.insert(std::make_pair(name, mod));
	}
}

ModLinker::~ModLinker() = default;

std::shared_ptr<const IMod> ModLinker::getMod(const std::string &modId) const
{
	// TODO: check for dependency and warn if not found?
	if (auto it = mods_.find(modId); it != mods_.end())
		return it->second;
	return {};
}