#pragma once

#include <memory>
#include <string>
#include <map>

#include <ICore.hpp>
#include <manager/ModManager.hpp>
#include <system/IEnvironmentBuilder.hpp>
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>

namespace CubA4::startup
{
	class BlockSetup
	{
	public:
		explicit BlockSetup();
		~BlockSetup();

		void load(std::shared_ptr<const ICore> core, std::shared_ptr<manager::ModManager> manager);
		void init(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder);
	private:
		std::shared_ptr<const ICore> core_;
		std::shared_ptr<manager::ModManager> manager_;
		std::shared_ptr<CubA4::logging::ILoggerTagged> log_;
	};
}