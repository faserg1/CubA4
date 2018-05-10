#ifndef IWORLDSUBSCRIBER_HPP
#define IWORLDSUBSCRIBER_HPP

namespace CubA4
{
	namespace world
	{
		class IWorldSubscriber
		{
		public:
			virtual ~IWorldSubscriber() {}
		protected:
			explicit IWorldSubscriber() {}
		};
	}
}

#endif // IWORLDSUBSCRIBER_HPP