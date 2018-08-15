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
				virtual const IVersion &version() const = 0;
				virtual const std::string &name() const = 0;
				virtual const std::wstring &locName() const = 0;
			protected:
				explicit IApplicationInfo() = default;
				virtual ~IApplicationInfo() = default;
			private:
			};
		}
	}
}

#endif // IAPPLICATIONINFO_HPP
