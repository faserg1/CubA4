#ifndef SUBSCRIPTIONHELPER_HPP
#define SUBSCRIPTIONHELPER_HPP

#include <vector>
#include <util/ISubscription.hpp>
#include <functional>
#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace util
		{
			template <class TSubscriber>
			class SubscriptionHelper
			{
				class Subscription;
			public:
				explicit SubscriptionHelper()
				{
					subscribers_ = std::make_shared<std::vector<TSubscriber*>>();
				}
				virtual ~SubscriptionHelper() = default;
				std::unique_ptr<ISubscription> add(TSubscriber *subscriber)
				{
					auto placed_subscriber = subscribers_->insert(subscribers_->end(), subscriber);
					std::weak_ptr<std::vector<TSubscriber*>> weakSubscribers = subscribers_;
					auto unsubscribeFunc = [placed_subscriber, weakSubscribers]()
					{
						if (auto subscribers = weakSubscribers.lock())
						{
							subscribers->erase(placed_subscriber);
						}
					};
					return std::move(std::make_unique<SubscriptionHelper<TSubscriber>::Subscription>(unsubscribeFunc));
				}
				void apply(std::function<void(TSubscriber *)> func)
				{
					for (auto subscriber : *subscribers_)
					{
						func(subscriber);
					}
				}
			private:
				std::shared_ptr<std::vector<TSubscriber*>> subscribers_;
			private:
				class Subscription :
					public virtual ISubscription
				{
				public:
					Subscription(std::function<void()> unsubscribeFunc)
						: unsubscribeFunc_(unsubscribeFunc), alreadyUnsubscribed_(false)
					{

					}
					~Subscription()
					{
						unsubscribe();
					}
					void unsubscribe() override
					{
						if (!alreadyUnsubscribed_)
							unsubscribeFunc_();
						alreadyUnsubscribed_ = true;
					}
				private:
					const std::function<void()> unsubscribeFunc_;
					bool alreadyUnsubscribed_;
				};
			};
		}
	}
}

#endif // SUBSCRIPTIONHELPER_HPP