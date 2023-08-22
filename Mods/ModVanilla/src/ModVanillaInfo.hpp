#pragma once

#include <IModInfo.hpp>
#include <memory>

namespace CubA4:: mod
{
	class ModVanillaInfo :
		public virtual IModInfo
	{
	public:
		ModVanillaInfo();
		~ModVanillaInfo();

		std::string getIdName() const override;
		std::wstring getName() const override;

		const info::IVersion &getVersion() const override;
		const info::IVersionDependency &getAppDependency() const override;
		std::vector<std::string> getRequiredMods() const override;
		std::vector<std::string> getPreferedMods() const override;
		const info::IVersionDependency &getModDependency(std::string modIdName) const override;

		std::shared_ptr<IMod> createMod() const override;
	private:
	};
}
