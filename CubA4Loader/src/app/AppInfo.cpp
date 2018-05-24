#include "./AppInfo.hpp"
#include "./AppVersion.hpp"
using namespace CubA4::app;

namespace
{
	AppVersion appVersion;
}

AppInfo::AppInfo() :
	name_("CubA4 Loader"), wname_(L"CubA4 Загрузчик")
{
	
}

AppInfo::~AppInfo()
{
	
}

const CubA4::core::info::IVersion &AppInfo::version() const
{
	return appVersion;
}

const std::string &AppInfo::name() const
{
	return name_;
}

const std::wstring &AppInfo::locName() const
{
	return wname_;
}