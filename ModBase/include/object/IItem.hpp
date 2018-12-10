#ifndef MODBASE_IITEM_HPP
#define MODBASE_IITEM_HPP

#include "IEntity.hpp"

namespace CubA4
{
	namespace mod
	{
		namespace object
		{
			class IItem :
				public virtual IEntity
			{
			public:
				virtual ~IItem() = default;
			protected:
				explicit IItem() = default;
			};
		}
	}
}

#endif // MODBASE_IITEM_HPP