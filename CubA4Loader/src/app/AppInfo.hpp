#ifndef CUBA4LOADER_APPINFO_HPP
#define CUBA4LOADER_APPINFO_HPP

#include <info/IApplicationInfo.hpp>

namespace CubA4
{
	namespace app
	{
		class AppInfo :
			public virtual CubA4::info::IApplicationInfo
		{
		public:
			explicit AppInfo();
			~AppInfo();
			
			const CubA4::info::IVersion &version() const override;
			const std::string &name() const override;
			const std::wstring &locName() const override;
		protected:
		private:
			std::string name_;
			std::wstring wname_;
		};
	}
}

#endif // CUBA4LOADER_APPINFO_HPP
