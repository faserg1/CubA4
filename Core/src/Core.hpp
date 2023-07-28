#pragma once

#include <memory>
#include <ICore.hpp>
#include <system/Environment.hpp>
#include <object/EntityManager.hpp>
#include <game/IGame.hpp>
#include <CoreExportHelper.hpp>
#include <config/CoreConfig.hpp>

namespace CubA4
{
	class Core final :
		public virtual ICore, public std::enable_shared_from_this<Core>
	{
	public:
		explicit Core(int argc, const char *const argv[], ApplicationFlags flags);
		~Core();

		ApplicationFlags getApplicationFlags() const override;
		ApplicationModeFlags getApplicationModeFlags() const override;
		const std::shared_ptr<const config::IFilePaths> getPaths() const override;
		std::shared_ptr<config::ICoreConfig> getConfig() const override;
		std::shared_ptr<logging::ILogger> getLogger() const override;
		std::shared_ptr<model::IModelFactory> getModelFactory() const override;
		std::shared_ptr<const resources::IResourcesManager> getResourcesManager() const override;
		std::shared_ptr<system::Environment> getEnvironment();
		std::shared_ptr<const system::IEnvironment> getEnvironment() const override;
		std::shared_ptr<const game::IGame> getGame() const override;
		std::shared_ptr<system::IRuntime> getRuntime() override;

		std::shared_ptr<object::EntityManager> getEntityManager();

		void setApplicationModeFlags(ApplicationModeFlags flags) override;

		void setEnvironment(std::shared_ptr<system::Environment> env);
		void setGame(std::shared_ptr<game::IGame> game);

		void criticalException() const override;
	protected:
	private:
		const ApplicationFlags appFlags_;
		const std::shared_ptr<const config::IFilePaths> paths_;
		std::shared_ptr<config::CoreConfig> config_;
		std::shared_ptr<logging::ILogger> logger_;
		std::shared_ptr<model::IModelFactory> modelFactory_;
		std::shared_ptr<resources::IResourcesManager> resourceManager_;
		std::shared_ptr<system::IRuntime> runtime_;
		std::shared_ptr<system::Environment> env_;
		std::shared_ptr<game::IGame> game_;
		std::shared_ptr<object::EntityManager> entityManager_;

		ApplicationModeFlags appModeFlags_ = {};
	};
}
