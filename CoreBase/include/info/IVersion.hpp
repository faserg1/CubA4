#ifndef IVERSION_HPP
#define IVERSION_HPP

#include <string>

namespace CubA4
{
	namespace core
	{
		namespace info
		{
			class IVersion
			{
			public:
				virtual unsigned short major() const = 0;
				virtual unsigned short minor() const = 0;
				virtual unsigned short patch() const = 0;
				
				virtual int build() const = 0;
				virtual int revision() const = 0;
				
				virtual std::string to_string() const = 0;
			protected:
				explicit IVersion() {}
				virtual ~IVersion() {}
			private:
			};
		}
	}
}

#endif // IVERSION_HPP
