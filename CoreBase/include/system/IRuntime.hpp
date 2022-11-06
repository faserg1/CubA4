#pragma once

#include <string>

namespace CubA4::system
{
	class IRuntime
	{
	public:
		virtual void addModuleSearchPath(const std::string &path) = 0;
	protected:
		virtual ~IRuntime() = default;
		explicit IRuntime() = default;
	};
}
