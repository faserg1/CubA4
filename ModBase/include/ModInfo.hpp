#ifndef MOD_INFO_HPP
#define MOD_INFO_HPP

#include <string>

namespace CubA4
{
	namespace mod
	{
		class ModInfo
		{
		public:
			virtual ~ModInfo() {}
			
			virtual std::string getIdName() = 0;
			virtual std::wstring getName() = 0;
			
			virtual void getVersion(int16_t &major, int16_t &minor, int16_t &patch) = 0;
		};
	}
}

#endif // MOD_INFO_HPP