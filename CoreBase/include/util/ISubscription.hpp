#ifndef COREBASE_ISUBSCRIPTION_HPP
#define COREBASE_ISUBSCRIPTION_HPP

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

#endif // COREBASE_ISUBSCRIPTION_HPP
