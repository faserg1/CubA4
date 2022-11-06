#pragma once

#include <memory>
#include <ICore.hpp>
#include <system/IEnvironmentBuilder.hpp>
#include <logging/ILogger.hpp>
#include <object/IBlock.hpp>
#include <manager/ModManager.hpp>

namespace CubA4::startup
{
	class WorldSetup
	{
	public:
		explicit WorldSetup();
		~WorldSetup();

		void load(std::shared_ptr<const ICore> core, std::shared_ptr<manager::ModManager> manager);
		void init(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder);
		void done();
	protected:
	private:
		std::shared_ptr<const ICore> core_;
		std::shared_ptr<manager::ModManager> manager_;
		std::shared_ptr<CubA4::logging::ILoggerTagged> log_;

		std::shared_ptr<const CubA4::object::IBlock> testBlock_;
	};
}
