#ifndef IMODVANILLA_HPP
#define IMODVANILLA_HPP

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

#endif // IMODVANILLA_HPP
