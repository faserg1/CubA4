#pragma once

#include <mod/IMod.hpp>

namespace CubA4
{
	namespace mod
	{
		class IModVanilla :
			public virtual IMod
		{
		public:
			virtual ~IModVanilla() = default;
		protected:
			explicit IModVanilla() = default;
		private:
		};
	}
}
