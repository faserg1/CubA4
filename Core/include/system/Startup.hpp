#ifndef STARTUP_HPP
#define STARTUP_HPP

#include <system/IStartup.hpp>
#include <memory>

namespace CubA4
{
	namespace mod
	{
		class IModLoader;
	}

	namespace core
	{
		class ICore;

		namespace system
		{
			class IAppCallback;

			class Startup :
				public virtual IStartup
			{
			public:
				explicit Startup(std::weak_ptr<const ICore> core);
				~Startup();

				void setup(system::IAppCallback &appCallback) override;

				void run() override;
				void stop() override;
			protected:
				void initMods();
				void unloadMods();

			private:
				const std::weak_ptr<const ICore> core_;
				system::IAppCallback *appCallback_;
				std::shared_ptr<mod::IModLoader> modLoader_;
			};
		}
	}
}

#endif // STARTUP_HPP
