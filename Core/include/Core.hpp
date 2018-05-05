#ifndef CORE_HPP
#define CORE_HPP

#include <CoreBase.hpp>
#include <CoreExportHelper.hpp>

namespace CubA4
{
	namespace core
	{
		class CoreConfig;

		class CORE_LIBRARY_EXPORT Core :
			public virtual CoreBase
		{
		public:
			explicit Core();
			~Core();

			std::shared_ptr<CoreConfigBase> getConfig();
		private:
			std::shared_ptr<CoreConfig> config_;
		};
	}
}

#endif // CORE_HPP