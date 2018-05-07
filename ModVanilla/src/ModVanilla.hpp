#ifndef MOD_VANILLA_HPP
#define MOD_VANILLA_HPP

#include <ModInfo.hpp>

namespace CubA4
{
	namespace mod
	{
		class ModVanilla :
			public virtual ModInfo
		{
		public:
			std::string getIdName() override;
			std::wstring getName() override;

			void getVersion(int16_t &major, int16_t &minor, int16_t &patch) override;
		};
	}
}

#endif // MOD_VANILLA_HPP