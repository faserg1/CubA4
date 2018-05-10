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
			virtual ~IEntity() {}
		protected:
			explicit IEntity() {}
		};
	}
}


#endif // IENTITY_HPP