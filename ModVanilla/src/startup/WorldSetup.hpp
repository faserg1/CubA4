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
		namespace object
		{
			class IBlock;
		}

		namespace world
		{
			class IWorld;
		}

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
				void done();
			protected:
			private:
				std::shared_ptr<manager::ModManager> manager_;
				std::shared_ptr<CubA4::core::logging::ILoggerTagged> log_;

				std::shared_ptr<const CubA4::mod::object::IBlock> testBlock_;
				std::shared_ptr<const CubA4::mod::world::IWorld> testWorld_;
			};
		}
	}
}

#endif // MODVANILLA_WORLDSETUP_HPP
