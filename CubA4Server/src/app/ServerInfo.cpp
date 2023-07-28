#include <app/ServerInfo.hpp>
#include <app/ServerVersion.hpp>
using namespace CubA4::app;

namespace
{
	ServerVersion appVersion;
}

ServerInfo::ServerInfo() :
	name_("CubA4 Server"), wname_(L"CubA4 Сервер")
{
	
}

ServerInfo::~ServerInfo()
{
	
}

const CubA4::info::IVersion &ServerInfo::version() const
{
	return appVersion;
}

const std::string &ServerInfo::name() const
{
	return name_;
}

const std::wstring &ServerInfo::locName() const
{
	return wname_;
}