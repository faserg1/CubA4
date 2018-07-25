#include "ModLibrary.hpp"
#include <IModInfo.hpp>
using namespace CubA4::mod;

ModLibrary::ModLibrary(boost::filesystem::path path) :
	importSymbolName_("getModInfo"),
	library_(path)
{
	if (!library_.has(importSymbolName_))
	{
		return;
	}
	auto getModInfo = library_.get<IModInfo *()>(importSymbolName_);
	modInfo_ = std::shared_ptr<IModInfo>(getModInfo());
	validLibrary_ = true;
}

bool ModLibrary::isValidLibrary() const
{
	return validLibrary_;
}

std::shared_ptr<const IModInfo> ModLibrary::getModInfo() const
{
	return modInfo_;
}