#ifndef MODVANILLA_WORLDSETUP_HPP
#define MODVANILLA_WORLDSETUP_HPP

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
		namespace manager
		{
			class ModManager;
		}

		namespace startup
		{
			class WorldSetup
			{
			public:
				explicit WorldSetup();
				~WorldSetup();

				void load(std::shared_ptr<const core::ICore> core, std::shared_ptr<manager::ModManager> manager);
				void init(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder);
			protected:
			private:
				std::shared_ptr<manager::ModManager> manager_;
				std::shared_ptr<CubA4::core::logging::ILoggerTagged> log_;
			};
		}
	}
}

#endif // MODVANILLA_WORLDSETUP_HPP
