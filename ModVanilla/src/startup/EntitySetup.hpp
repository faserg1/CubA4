#pragma once

#include <memory>
#include <ICore.hpp>
#include <manager/ModManager.hpp>
#include <system/IEnvironmentBuilder.hpp>

namespace CubA4::startup
{
	class EntitySetup
	{
	public:
		explicit EntitySetup();
		~EntitySetup();

		void load(std::shared_ptr<const ICore> core, std::shared_ptr<manager::ModManager> manager);
		void preinit(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder);
		void init(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder);
	private:
		std::shared_ptr<const CubA4::ICore> core_;
		std::shared_ptr<manager::ModManager> manager_;
		std::shared_ptr<CubA4::logging::ILoggerTagged> log_;
	};
}