#ifndef BASE_ENTITY_HPP
#define BASE_ENTITY_HPP

#include "BaseObject.hpp"

namespace CubA4
{
	namespace object
	{
		class BaseEntity :
			public virtual BaseObject
		{
		public:
			virtual ~BaseEntity() {}
		protected:
			explicit BaseEntity() {}
		};
	}
}


#endif // BASE_ENTITY_HPP