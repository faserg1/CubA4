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
			const std::string &name() const override;
			const std::wstring &locName() const override;
		protected:
		private:
			std::string name_;
			std::wstring wname_;
		};
	}
}

#endif // APPINFO_HPP
