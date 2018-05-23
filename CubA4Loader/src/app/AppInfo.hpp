#ifndef APPINFO_HPP
#define APPINFO_HPP

#include <info/IApplicationInfo.hpp>

namespace CubA4
{
	namespace app
	{
		class AppInfo :
			public virtual CubA4::core::info::IApplicationInfo
		{
		public:
			explicit AppInfo();
			~AppInfo();
			
			const CubA4::core::info::IVersion &version() const override;
			std::string name() const override;
			std::wstring locName() const override;
		protected:
		private:
		};
	}
}

#endif // APPINFO_HPP
