#pragma once

#include <memory>
#include <manager/IModManager.hpp>

namespace CubA4::manager
{
	class ModManager :
		public virtual IModManager
	{
	public:
		explicit ModManager();
		~ModManager();
	protected:
	private:
	};
}

