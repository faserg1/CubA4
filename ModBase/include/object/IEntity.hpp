#ifndef MODBASE_IENTITY_HPP
#define MODBASE_IENTITY_HPP

#include "IObject.hpp"

namespace CubA4
{
	namespace mod
	{
		namespace object
		{
			class IEntity :
				public virtual IObject
			{
			public:
				virtual ~IEntity() = default;
			protected:
				explicit IEntity() = default;
			};
		}
	}
}


#endif // MODBASE_IENTITY_HPP