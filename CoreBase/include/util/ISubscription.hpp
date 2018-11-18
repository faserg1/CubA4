#ifndef ISUBSCRIPTION_HPP
#define ISUBSCRIPTION_HPP

namespace CubA4
{
	namespace core
	{
		namespace util
		{
			class ISubscription
			{
			public:
				virtual ~ISubscription() = default;
				virtual void unsubscribe() = 0;
			protected:
				explicit ISubscription() = default;
			private:
			};
		}
	}
}

#endif // ISUBSCRIPTION_HPP
