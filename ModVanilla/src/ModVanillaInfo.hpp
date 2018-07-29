#ifndef MODVANILLAINFO_HPP
#define MODVANILLAINFO_HPP

#include <IModInfo.hpp>

namespace CubA4
{
	namespace mod
	{
		class ModVanillaInfo :
			public virtual IModInfo
		{
		public:
			ModVanillaInfo();
			~ModVanillaInfo();

			std::string getIdName() const override;
			std::wstring getName() const override;

			const core::info::IVersion &getVersion() const override;
			const core::info::IVersionDependency &getAppDependency() const override;
			std::vector<std::string> getRequiredMods() const override;
			std::vector<std::string> getPreferedMods() const override;
			const core::info::IVersionDependency &getModDependency(std::string modIdName) const override;

			std::shared_ptr<IMod> getMod() const override;
		private:
			std::shared_ptr<IMod> mod_;
		};
	}
}

#endif // MODVANILLAINFO_HPP