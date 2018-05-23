#include "./AppInfo.hpp"
#include "./AppVersion.hpp"
using namespace CubA4::app;

namespace
{
	AppVersion appVersion;
}

AppInfo::AppInfo()
{
	
}

AppInfo::~AppInfo()
{
	
}

const CubA4::core::info::IVersion &AppInfo::version() const
{
	return appVersion;
}

std::string AppInfo::name() const
{
	return "CubA4 Loader";
}

std::wstring AppInfo::locName() const
{
	return L"CubA4 Загрузчик";
}