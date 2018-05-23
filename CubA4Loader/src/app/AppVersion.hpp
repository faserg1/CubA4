#ifndef APPVERSION_HPP
#define APPVERSION_HPP

#include <info/IVersion.hpp>

namespace CubA4
{
	namespace app
	{
		class AppVersion :
			public virtual CubA4::core::info::IVersion
		{
		public:
			explicit AppVersion();
			~AppVersion();
			
			unsigned short major() const override;
			unsigned short minor() const override;
			unsigned short patch() const override;
			
			int build() const override;
			int revision() const override;
			
			std::string to_string() const override;
		protected:
		private:
		};
	}
}

#endif // APPVERSION_HPP
