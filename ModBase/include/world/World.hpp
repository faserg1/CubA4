#ifndef WOLRD_HPP
#define WOLRD_HPP

#include <string>
#include "../object/BaseObject.hpp"

namespace CubA4
{
	namespace world
	{
		class WorldSubscriber;

		class World :
			public virtual CubA4::object::BaseObject
		{
		public:
			virtual ~World() {}

			virtual void subscribe(WorldSubscriber *subscriber) = 0;
			virtual void unsubscribe(WorldSubscriber *subscriber) = 0;
		protected:
			explicit World() {}
		};
	}
}

#endif // WOLRD_HPP