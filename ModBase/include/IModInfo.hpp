#ifndef IMODINFO_HPP
#define IMODINFO_HPP

#include <string>

namespace CubA4
{
	namespace mod
	{
		class IModInfo
		{
		public:
			virtual ~IModInfo() {}
			
			virtual std::string getIdName() = 0;
			virtual std::wstring getName() = 0;
			
			virtual void getVersion(int16_t &major, int16_t &minor, int16_t &patch) = 0;
		protected:
			explicit IModInfo() {}
		};
	}
}

#endif // IMODINFO_HPP