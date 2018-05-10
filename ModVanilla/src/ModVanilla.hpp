#ifndef MODVANILLA_HPP
#define MODVANILLA_HPP

#include <IModInfo.hpp>

namespace CubA4
{
	namespace mod
	{
		class ModVanilla :
			public virtual IModInfo
		{
		public:
			std::string getIdName() override;
			std::wstring getName() override;

			void getVersion(int16_t &major, int16_t &minor, int16_t &patch) override;
		};
	}
}

#endif // MODVANILLA_HPP