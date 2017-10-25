#include <string>

namespace CubA4
{
	namespace Mod
	{
		class ModInfo
		{
		public:
			virtual ~ModInfo() {}
			
			std::wstring getName() = 0;
			std::string getIdName() = 0;
			
			void getVersion(int16_t &major, int16_t &minor, int16_t &patch) = 0;
		};
	}
}