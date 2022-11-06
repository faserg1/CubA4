#pragma once

#include <system/IRuntime.hpp>

namespace CubA4::system
{
	class Runtime : public virtual IRuntime
	{
	public:
		explicit Runtime();
		~Runtime();

		void addModuleSearchPath(const std::string &path);
	};
}
