#ifndef WORLDSUBSCRIBER_HPP
#define WORLDSUBSCRIBER_HPP

namespace CubA4
{
	namespace world
	{
		class WorldSubscriber
		{
		public:
			virtual ~WorldSubscriber() {}
		protected:
			explicit WorldSubscriber() {}
		};
	}
}

#endif // WORLDSUBSCRIBER_HPP