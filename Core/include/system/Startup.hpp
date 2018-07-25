#ifndef STARTUP_HPP
#define STARTUP_HPP

#include <system/IStartup.hpp>
#include <memory>

namespace CubA4
{
	namespace core
	{
		class ICore;

		namespace system
		{
			class Startup :
				public virtual IStartup
			{
			public:
				explicit Startup(std::weak_ptr<const ICore> core);
				~Startup();
			protected:
			private:
				std::weak_ptr<const ICore> core_;
			};
		}
	}
}

#endif // STARTUP_HPP
