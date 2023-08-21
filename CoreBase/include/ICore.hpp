#pragma once

#include <memory>
#include <ApplicationFlags.hpp>
#include <ApplicationModeFlags.hpp>
#include <model/IModelFactory.hpp>
#include <audio/IAudioManager.hpp>
#include <config/IFilePaths.hpp>
#include <config/ICoreConfig.hpp>
#include <logging/ILogger.hpp>
#include <resources/IResourcesManager.hpp>
#include <physics/IPhysicsManager.hpp>
#include <core/IRuntime.hpp>
#include <core/IEnvironment.hpp>
#include <game/IGame.hpp>

namespace CubA4
{
	class ICore
	{
	public:
		virtual ApplicationFlags getApplicationFlags() const = 0;
		virtual ApplicationModeFlags getApplicationModeFlags() const = 0;
		//Функции, помеченные const, будут доступны везде.
		//В основном ICore передается как std::shared_ptr<const ICore>, из чего следует, что будут доступны только эти функции

		///Получает основные пути
		virtual const std::shared_ptr<const config::IFilePaths> getPaths() const = 0;
		///Получает конфигурацию приложения
		virtual std::shared_ptr<config::ICoreConfig> getConfig() const = 0;
		///Получает логгер
		virtual std::shared_ptr<logging::ILogger> getLogger() const = 0;
		///Получает менеджер ресурсов
		virtual std::shared_ptr<model::IModelFactory> getModelFactory() const = 0;
		virtual std::shared_ptr<const resources::IResourcesManager> getResourcesManager() const = 0;
		virtual std::shared_ptr<const core::IEnvironment> getEnvironment() const = 0;
		// TODO: make const, move import to builder
		virtual std::shared_ptr<audio::IAudioManager> getAudioManager() const = 0;
		virtual std::shared_ptr<const game::IGame> getGame() const = 0;
		virtual std::shared_ptr<const physics::IPhysicsManager> getPhysicsManager() const = 0;
		///Создает сообщение о критической ошибке
		virtual void criticalException() const = 0;

		//Функции, не помеченные const будут доступны только основному приложению, или там, где ICore не передается по константному указателю.
		//К примеру, через std::shared_ptr<ICore> будут доступны эти функции

		virtual std::shared_ptr<core::IRuntime> getRuntime() = 0;
		virtual void setApplicationModeFlags(ApplicationModeFlags flags) = 0;
	protected:
		virtual ~ICore() = default;
		explicit ICore() = default;
	};
}
