#pragma once

#include <string>
#include <vector>
#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace info
		{
			class IVersion;
			class IVersionDependency;
		}
	}

	namespace mod
	{
		class IMod;

		class IModInfo
		{
		public:
			virtual ~IModInfo() = default;
			
			virtual std::string getIdName() const = 0;
			virtual std::wstring getName() const = 0;
			
			virtual const core::info::IVersion &getVersion() const = 0;
			virtual const core::info::IVersionDependency &getAppDependency() const = 0;
			virtual std::vector<std::string> getRequiredMods() const = 0;
			virtual std::vector<std::string> getPreferedMods() const = 0;
			virtual const core::info::IVersionDependency &getModDependency(std::string modIdName) const = 0;

			virtual std::shared_ptr<IMod> createMod() const = 0;
		protected:
			explicit IModInfo() = default;
		};
	}
}
