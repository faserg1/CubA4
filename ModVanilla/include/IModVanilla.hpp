#ifndef MODVANILLA_IMODVANILLA_HPP
#define MODVANILLA_IMODVANILLA_HPP

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

#endif // MODVANILLA_IMODVANILLA_HPP
