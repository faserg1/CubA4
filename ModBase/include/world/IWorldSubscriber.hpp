#ifndef IWORLDSUBSCRIBER_HPP
#define IWORLDSUBSCRIBER_HPP

namespace CubA4
{
	namespace mod
	{
		namespace world
		{
			class IWorldSubscriber
			{
			public:
				virtual ~IWorldSubscriber() = default;
			protected:
				explicit IWorldSubscriber() = default;
			};
		}
	}
}

#endif // IWORLDSUBSCRIBER_HPP