#ifndef IAPPCALLBACK_HPP
#define IAPPCALLBACK_HPP

#include <memory>

namespace CubA4
{
	namespace mod
	{
		class IModLoader;
	}

	namespace core
	{
		namespace system
		{
			class IAppCallback
			{
			public:
				virtual std::shared_ptr<mod::IModLoader> getModLoader() const = 0;
			protected:
				virtual ~IAppCallback() = default;
				explicit IAppCallback() = default;
			private:
			};
		}
	}
}

#endif // IAPPCALLBACK_HPP
