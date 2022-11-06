#pragma once

namespace CubA4::util
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
