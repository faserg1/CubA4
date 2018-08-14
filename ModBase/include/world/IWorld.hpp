#ifndef IWOLRD_HPP
#define IWOLRD_HPP

#include <string>
#include "../object/IObject.hpp"

namespace CubA4
{
	namespace world
	{
		class IWorldSubscriber;

		class IWorld :
			public virtual CubA4::object::IObject
		{
		public:
			virtual ~IWorld() = default;

			virtual void subscribe(IWorldSubscriber *subscriber) = 0;
			virtual void unsubscribe(IWorldSubscriber *subscriber) = 0;
		protected:
			explicit IWorld() = default;
		};
	}
}

#endif // IWOLRD_HPP