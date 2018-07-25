#include "ModLibrary.hpp"
using namespace CubA4::loader;
using namespace CubA4::mod;

ModLibrary::ModLibrary(boost::filesystem::path path) :
	importSymbolName_("getModInfo"),
	library_(path)
{
	if (!library_.has(importSymbolName_))
	{
		return;
	}
	auto getModInfo = library_.get<ModInfo *()>(importSymbolName_);
	modInfo_ = std::shared_ptr<ModInfo>(getModInfo());
	validLibrary_ = true;
}

bool ModLibrary::isValidLibrary() const
{
	return validLibrary_;
}

std::shared_ptr<const ModInfo> ModLibrary::getModInfo() const
{
	return modInfo_;
}