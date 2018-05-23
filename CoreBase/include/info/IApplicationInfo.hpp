#ifndef IAPPLICATIONINFO_HPP
#define IAPPLICATIONINFO_HPP

#include <string>

namespace CubA4
{
	namespace core
	{
		namespace info
		{
			class IVersion;
			
			class IApplicationInfo
			{
			public:
				virtual ~IApplicationInfo() {}
				
				virtual const IVersion &version() const = 0;
				virtual std::string name() const = 0;
				virtual std::wstring locName() const = 0;
			protected:
				explicit IApplicationInfo() {}
			private:
			};
		}
	}
}

#endif // IAPPLICATIONINFO_HPP
