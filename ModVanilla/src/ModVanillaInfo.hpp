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
			std::string getIdName() override;
			std::wstring getName() override;

			void getVersion(int16_t &major, int16_t &minor, int16_t &patch) override;
		};
	}
}

#endif // MODVANILLAINFO_HPP