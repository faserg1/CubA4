#ifndef ICORE_HPP
#define ICORE_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		class ICoreConfig;

		class ICore
		{
		public:
			virtual std::shared_ptr<ICoreConfig> getConfig() = 0;

			virtual ~ICore() {}
		protected:
			explicit ICore() {}
		};
	}
}

#endif // ICORE_HPP