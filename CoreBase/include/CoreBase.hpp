#ifndef COREBASE_HPP
#define COREBASE_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		class CoreConfigBase;

		class CoreBase
		{
		public:
			virtual std::shared_ptr<CoreConfigBase> getConfig() = 0;

			virtual ~CoreBase() {}
		protected:
			explicit CoreBase() {}
		};
	}
}

#endif // COREBASE_HPP