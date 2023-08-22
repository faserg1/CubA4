#include "ModVanillaInfo.hpp"
#include <ModExportHelper.hpp>

extern "C"
{
	MOD_LIBRARY_EXPORT ::CubA4::mod::IModInfo *getModInfo()
	{
		return new ::CubA4::mod::ModVanillaInfo();
	}
}

