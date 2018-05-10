#ifndef IITEM_HPP
#define IITEM_HPP

#include "IEntity.hpp"

namespace CubA4
{
	namespace object
	{
		class IItem :
			public virtual IEntity
		{
		public:
			virtual ~IItem() {}
		protected:
			explicit IItem() {}
		};
	}
}

#endif // IITEM_HPP