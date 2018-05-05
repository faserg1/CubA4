#ifndef CORE_HPP
#define CORE_HPP

#include <CoreBase.hpp>
#include <CoreExportHelper.hpp>

namespace CubA4
{
	namespace core
	{
		class CORE_LIBRARY_EXPORT Core :
			public virtual CoreBase
		{
		public:
			explicit Core();
			~Core();
		};
	}
}

#endif // CORE_HPP