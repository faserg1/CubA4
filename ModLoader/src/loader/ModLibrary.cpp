#include "ModLibrary.hpp"

CubA4::loader::ModLibrary::ModLibrary(boost::filesystem::path path) :
	importSymbolName_("getModInfo"),
	library_(path)
{
	if (!library_.has(importSymbolName_))
	{
		return;
	}
	auto getModInfo = library_.get<CubA4::mod::ModInfo *()>(importSymbolName_);
	modInfo_ = getModInfo();
	validLibrary_ = true;
}

bool CubA4::loader::ModLibrary::isValidLibrary()
{
	return validLibrary_;
}
