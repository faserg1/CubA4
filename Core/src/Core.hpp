#pragma once

#include <memory>
#include <ICore.hpp>
#include <core/Environment.hpp>
#include <game/IGame.hpp>
#include <CoreExportHelper.hpp>
#include <config/CoreConfig.hpp>

namespace CubA4
{

	namespace physics
	{
		class PhysicsManager;
	}

	namespace audio
	{
		class AudioManager;
	}

	namespace object
	{
		class EntityManager;
	}

	namespace core
	{
		class Startup;
	}

	namespace render
	{
		class IRenderInfo;

		namespace engine
		{
			class IRenderManager;
		}
	}

	
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
		std::shared_ptr<core::Environment> getEnvironment();
		std::shared_ptr<const core::IEnvironment> getEnvironment() const override;
		std::shared_ptr<audio::IAudioManager> getAudioManager() const override;
		std::shared_ptr<const game::IGame> getGame() const override;
		std::shared_ptr<core::IRuntime> getRuntime() override;

		std::shared_ptr<object::EntityManager> getEntityManager();
		std::shared_ptr<const physics::IPhysicsManager> getPhysicsManager() const override;
		std::shared_ptr<physics::PhysicsManager> getPhysicsManager();

		std::shared_ptr<render::engine::IRenderManager> getRenderManager() const;
		const render::IRenderInfo *getRenderInfo() const;

		void setApplicationModeFlags(ApplicationModeFlags flags) override;

		void setEnvironment(std::shared_ptr<core::Environment> env);
		void setGame(std::shared_ptr<game::IGame> game);

		void setStartup(CubA4::core::Startup *startup);

		void criticalException() const override;

		void onLoad();
		void onUnload();
	private:
		const ApplicationFlags appFlags_;
		const std::shared_ptr<const config::IFilePaths> paths_;
		std::shared_ptr<config::CoreConfig> config_;
		std::shared_ptr<logging::ILogger> logger_;
		std::shared_ptr<model::IModelFactory> modelFactory_;
		std::shared_ptr<resources::IResourcesManager> resourceManager_;
		std::shared_ptr<core::IRuntime> runtime_;
		std::shared_ptr<core::Environment> env_;
		std::shared_ptr<audio::AudioManager> audioManager_;
		std::shared_ptr<game::IGame> game_;
		std::shared_ptr<object::EntityManager> entityManager_;
		std::shared_ptr<physics::PhysicsManager> physicsManager_;

		CubA4::core::Startup *startup_;


		ApplicationModeFlags appModeFlags_ = {};
	};
}
