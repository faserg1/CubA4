#pragma once

#include <core/IRuntime.hpp>

namespace CubA4::core
{
	class Runtime : public virtual IRuntime
	{
	public:
		explicit Runtime();
		~Runtime();

		void addModuleSearchPath(const std::string &path);
	};
}
