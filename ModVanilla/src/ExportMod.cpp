#include "ModVanilla.hpp"
#include <ModExportHelper.hpp>

extern "C"
{
	MOD_LIBRARY_EXPORT ::CubA4::mod::ModInfo *getModInfo()
	{
		return new ::CubA4::mod::ModVanilla();
	}
}

