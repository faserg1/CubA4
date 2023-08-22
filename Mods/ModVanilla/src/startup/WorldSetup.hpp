#pragma once

#include <memory>
#include <ICore.hpp>
#include <core/IEnvironmentBuilder.hpp>
#include <logging/ILogger.hpp>
#include <manager/ModManager.hpp>
#include <world/IWorld.hpp>

namespace CubA4::startup
{
	class WorldSetup
	{
	public:
		using IdType = CubA4::core::IIdentityiMap::IdType;

		explicit WorldSetup();
		~WorldSetup();

		void load(std::shared_ptr<const ICore> core, std::shared_ptr<manager::ModManager> manager);
		void init(std::shared_ptr<CubA4::core::IEnvironmentBuilder> builder);
		void done();

		IdType getTestWorldId() const;
		IdType getTestDimensionId() const;
	protected:
	private:
		std::shared_ptr<const ICore> core_;
		std::shared_ptr<manager::ModManager> manager_;
		std::shared_ptr<CubA4::logging::ILoggerTagged> log_;

		std::shared_ptr<const CubA4::world::IWorld> testWorld_;
		std::shared_ptr<const CubA4::world::IDimension> testDimension_;

		IdType testWorldId_ = 0;
		IdType testDimensionId_ = 0;
	};
}
