#ifndef BASEBLOCK_HPP
#define BASEBLOCK_HPP

#include "BaseObject.hpp"
#include <cstdint>

namespace CubA4
{
	namespace object
	{
		class BaseBlock :
			public virtual BaseObject
		{
		public:
			virtual ~BaseBlock() {}
		protected:
			explicit BaseBlock() {}
		};
	}
}

#endif // BASEBLOCK_HPP