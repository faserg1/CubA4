#ifndef IENTITY_HPP
#define IENTITY_HPP

#include "IObject.hpp"

namespace CubA4
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


#endif // IENTITY_HPP