#pragma once

#include <info/IApplicationInfo.hpp>

namespace CubA4::app
{
	class ServerInfo :
		public virtual CubA4::info::IApplicationInfo
	{
	public:
		explicit ServerInfo();
		~ServerInfo();
		
		const CubA4::info::IVersion &version() const override;
		const std::string &name() const override;
		const std::wstring &locName() const override;
	protected:
	private:
		std::string name_;
		std::wstring wname_;
	};
}
