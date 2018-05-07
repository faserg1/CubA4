#ifndef BASEITEM_HPP
#define BASEITEM_HPP

#include "BaseEntity.hpp"

namespace CubA4
{
	namespace object
	{
		class BaseItem :
			public virtual BaseEntity
		{
		public:
		protected:
			explicit BaseItem() {}
		};
	}
}

#endif // BASEITEM_HPP