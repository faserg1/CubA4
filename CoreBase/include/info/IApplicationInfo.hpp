#pragma once

#include <string>
#include <info/IVersion.hpp>

namespace CubA4::info
{
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
