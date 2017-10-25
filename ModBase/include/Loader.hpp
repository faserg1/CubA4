/*
Необходимо включать, чтобы мод смог загрузится.
*/

#include <type_traits>
#include <stdexcept>
#include "ModInfo.hpp"

class ModInfoContainer final
{
	friend class RegisterMod;
	static ::CubA4::Mod::ModInfo *modInfo_ = nullptr;
	static void registerMod(::CubA4::Mod::ModInfo *modInfo)
	{
		if (modInfo_ != nullptr)
			throw std::runtime_error("Cannot register mod twice!");
		modInfo_ = modInfo;
	}
public:
	static ::CubA4::Mod::ModInfo *getModInfo() nothrow
	{
		return modInfo_;
	}
};

template <class TModType>
class RegisterMod final
{
	static_assert(std::is_base_of<::CubA4::Mod::ModInfo, TModType>::value,
		"Cannot register mod with invalid base class. Must be ModInfo.");
	static_assert(std::is_same<RegisterMod, ::RegisterMod>::value, "Include must not be in namespaces.");
public:
	RegisterMod()
	{
		auto mod = new TModType();
		ModInfoContainer::registerMod(mod);
	}
};

extern "C" GetModInfo()
{
	return ModInfoContainer::getModInfo();
}