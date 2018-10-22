#ifndef WORLDSETUP_HPP
#define WORLDSETUP_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		class ICore;

		namespace logging
		{
			class ILoggerTagged;
		}

		namespace system
		{
			class IEnvironmentBuilder;
		}
	}

	namespace mod
	{
		namespace startup
		{
			class WorldSetup
			{
			public:
				explicit WorldSetup();
				~WorldSetup();

				void load(std::shared_ptr<const core::ICore> core);
				void init(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder);
			protected:
			private:
				std::shared_ptr<CubA4::core::logging::ILoggerTagged> log_;
			};
		}
	}
}

#endif // WORLDSETUP_HPP
