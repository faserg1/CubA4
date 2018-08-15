#ifndef IBLOCK_HPP
#define IBLOCK_HPP

#include "IObject.hpp"
#include <cstdint>

namespace CubA4
{
	namespace object
	{
		class IBlock :
			public virtual IObject
		{
		public:
			virtual ~IBlock() = default;
		protected:
			explicit IBlock() = default;
		};
	}
}

#endif // IBLOCK_HPP