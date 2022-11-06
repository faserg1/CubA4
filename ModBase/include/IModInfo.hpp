#pragma once

#include <string>
#include <vector>
#include <memory>
#include <info/IVersion.hpp>
#include <info/IVersionDependency.hpp>
#include <mod/IMod.hpp>

namespace CubA4::mod
{
	class IModInfo
	{
	public:
		virtual ~IModInfo() = default;
		
		virtual std::string getIdName() const = 0;
		virtual std::wstring getName() const = 0;
		
		virtual const info::IVersion &getVersion() const = 0;
		virtual const info::IVersionDependency &getAppDependency() const = 0;
		virtual std::vector<std::string> getRequiredMods() const = 0;
		virtual std::vector<std::string> getPreferedMods() const = 0;
		virtual const info::IVersionDependency &getModDependency(std::string modIdName) const = 0;

		virtual std::shared_ptr<IMod> createMod() const = 0;
	protected:
		explicit IModInfo() = default;
	};
}

