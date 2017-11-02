/*
Необходимо включать, чтобы мод смог загрузится.
*/

#include <type_traits>
#include <stdexcept>
#include "ExportHelper.hpp"
#include "ModInfo.hpp"

class ModInfoContainer final
{
	template <class TModType>
	friend class RegisterModHelper;
	//
	static void *modInfo_;
	inline static void registerMod(::CubA4::mod::ModInfo *modInfo)
	{
		if (modInfo_ != nullptr)
			throw std::runtime_error("Cannot register mod twice!");
		modInfo_ = (void *) modInfo;
	}
public:
	inline static ::CubA4::mod::ModInfo *getModInfo()
	{
		return (::CubA4::mod::ModInfo *) modInfo_;
	}
};

template <class TModType>
class RegisterModHelper final
{
	static_assert(std::is_base_of<::CubA4::mod::ModInfo, TModType>::value,
		"Cannot register mod with invalid base class. Must be ModInfo.");
	static_assert(std::is_same<RegisterModHelper<TModType>, ::RegisterModHelper<TModType> >::value, "Include must not be in namespaces.");
public:
	RegisterModHelper()
	{
		auto mod = new TModType();
		ModInfoContainer::registerMod(mod);
	}
};

extern "C"
{
	LIBRARY_EXPORT CubA4::mod::ModInfo  *getModInfo()
	{
		return ModInfoContainer::getModInfo();
	}
}