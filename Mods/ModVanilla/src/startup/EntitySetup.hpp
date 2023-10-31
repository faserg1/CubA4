#pragma once

#include <memory>
#include <ICore.hpp>
#include <manager/ModManager.hpp>
#include <core/IEnvironmentBuilder.hpp>

namespace CubA4::mod
{
	class ModControl;
}

namespace CubA4::startup
{
	class EntitySetup
	{
	public:
		explicit EntitySetup(std::shared_ptr<const CubA4::mod::ModControl> modControl);
		~EntitySetup();

		void load(std::shared_ptr<const ICore> core, std::shared_ptr<manager::ModManager> manager);
		void preinit(std::shared_ptr<CubA4::core::IEnvironmentBuilder> builder);
		void init(std::shared_ptr<CubA4::core::IEnvironmentBuilder> builder);
	private:
		const std::shared_ptr<const CubA4::mod::ModControl> modControl_;
		std::shared_ptr<const CubA4::ICore> core_;
		std::shared_ptr<manager::ModManager> manager_;
		std::shared_ptr<CubA4::logging::ILoggerTagged> log_;
	};
}